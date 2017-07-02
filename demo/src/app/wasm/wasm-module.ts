// The "exported" C functions look like this.
export interface WasmModule {
    _drawCircles(numCircles: number, radius: number, canvasWidth: number): number;
}