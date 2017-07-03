import CounterWA from './wasm/counter.wasm';

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
      document.getElementById('counter').innerHTML = this.counterModule.exports._count();
    });
  }

  loadCounterWasm() {
    this.counterModule = new CounterWA({
      'env': {
        'memoryBase': 0,
        'tableBase': 0,
        'memory': new WebAssembly.Memory({initial: 256}),
        'table': new WebAssembly.Table({initial: 0, element: 'anyfunc'})
      }
    });
  }

}

