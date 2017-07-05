import CounterWA from '../build/counter.wasm';
import { loadWebAssembly } from './loader';

export class Counter {
  counterModule;

  constructor() {
    this.insertCounterGUI();
    this.loadCounterWasm();
  }

  insertCounterGUI() {
    // Insert Counter & Global method for UI
    document.querySelector('#app').insertAdjacentHTML('afterbegin', '<button id="count">Click me</button><div>Count: <span id="counter"></span></div>');
    const count = document.getElementById('count');
    count.addEventListener('click', () => {
      document.getElementById('counter').innerHTML = this.counterModule.exports.__ZN7Counter5countEv(); // @TODO why does WASM do this for class methods??
    });
  }

  loadCounterWasm() {

    const importObject = {
      'env': {
        'memoryBase': 0,
        'tableBase': 0,
        'memory': new WebAssembly.Memory({initial: 256}),
        'table': new WebAssembly.Table({initial: 0, element: 'anyfunc'}),
      }
    };
    loadWebAssembly('wasm/counter.wasm',importObject).then(instance => {
      console.log(instance);
    });
    this.counterModule = new CounterWA(importObject);
    console.log('Counter Module', this.counterModule);
  }

}

