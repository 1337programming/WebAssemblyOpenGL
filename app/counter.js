import CounterWA from '../build/counter.wasm';

export class Counter {
  counterModule;
  counterInstance;

  constructor() {
    this.insertCounterGUI();
    this.loadCounterWasm();
  }

  insertCounterGUI() {
    // Insert Counter & Global method for UI
    document.querySelector('#app').insertAdjacentHTML('afterbegin', '<button id="count">Click me</button><div>Count: <span id="counter"></span></div>');
    const count = document.getElementById('count');
    count.addEventListener('click', () => {
      document.getElementById('counter').innerHTML = this.counterInstance.exports.__ZN7Counter5countEv(); // @TODO why does WASM do this for class methods??
    });
  }

  loadCounterWasm() {

    const importObject = {
      'env': {
        'memoryBase': 0,
        'tableBase': 0,
        'memory': new WebAssembly.Memory({initial: 256}),
        'table': new WebAssembly.Table({initial: 4, element: 'anyfunc'}),
        'abort': function(msg) { console.error(msg); }
      }
    };
    new CounterWA(importObject).then(result => {
        this.counterModule = result.module;
        this.counterInstance = result.instance;

        console.log('Counter Module', this.counterModule);
        console.log('Counter Instance', this.counterInstance);
    });
  }
}

