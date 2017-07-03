import {WasmImports} from "./wasm-imports";
import {WasmModule} from "./wasm-module";
import Module = WebAssembly.Module;
import Memory = WebAssembly.Memory;
import Table = WebAssembly.Table;
import Instance = WebAssembly.Instance;

export class WasmLoader {

    async loadWasm(wasmImports: WasmImports, path: string = 'assets/main.wasm'): Promise<WasmModule> {
        // 1. Load the wasm file.
        const wasmFile: Response = await fetch(path);

        // 2. Get the Array Buffer
        const buffer: ArrayBuffer = await wasmFile.arrayBuffer();

        // 3. Compile the buffer.
        const mod: Module = await WebAssembly.compile(buffer);
        const imports: WasmImportObject = this.buildImports(wasmImports);

        // 3. Initiate, passing in the bytes source and the input params.
        const wasm: Instance = await WebAssembly.instantiate(mod, imports);

        // 4. Return the exports, as the defined WasmCode.
        console.log(wasm.exports);
        return wasm.exports as WasmModule;
    }

    private buildImports(wasmImports: WasmImports): WasmImportObject {
        const imports: WasmImportObject = {};
        imports.env = {
            _drawCircle: (x, y, r) => wasmImports.drawCircle(x, y, r)
        };
        imports.env.memoryBase = imports.env.memoryBase || 0;
        imports.env.tableBase = imports.env.tableBase || 0;
        if (!imports.env.memory) {
            imports.env.memory = new WebAssembly.Memory({initial: 256});
        }
        if (!imports.env.table) {
            imports.env.table = new WebAssembly.Table({initial: 0, element: 'anyfunc'});
        }
        return imports;
    }
}

export interface WasmImportObject {
    env?: {
        _drawCircle?: Function;
        memoryBase?: number;
        tableBase?: number;
        memory?: Memory;
        table?: Table;
    }

}