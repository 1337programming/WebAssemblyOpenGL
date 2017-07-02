import {Component, ElementRef, OnInit, ViewChild} from '@angular/core';
import {WasmLoader} from "./wasm-loader";
import {WasmDemo} from "./wasm-demo";
import {WasmModule} from "./wasm-module";

@Component({
  selector: 'app-wasm',
  templateUrl: './wasm.component.html',
  styleUrls: ['./wasm.component.css']
})
export class WasmComponent implements OnInit {

  @ViewChild('canvas') canvas: ElementRef;
  public numCircles: number = 5;
  public radius: number = 5;
  public context;
  public wasmDemo: WasmDemo;
  public wasmExports: WasmModule;
  public canvasWidth: number = 400;
  public canvasHeight: number = 200;
  constructor(
      public wasmLoader: WasmLoader
  ) { }

  async ngOnInit() {
    this.wasmDemo = new WasmDemo(this.canvas.nativeElement.getContext('2d'));
    this.wasmExports = await this.wasmLoader.loadWasm(this.wasmDemo);
  }

  drawCircles() {
    this.wasmExports._drawCircles(this.numCircles, this.radius, this.canvasWidth);
  }

}
