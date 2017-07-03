import Module from '../build/engine.js'

export class Engine {

  module;

  constructor() {
    this.loadDemoWasm();
  }

  loadDemoWasm() {
    this.module = Module({
      wasmBinaryFile: '/wasm/engine.wasm',
    });
  }

}

