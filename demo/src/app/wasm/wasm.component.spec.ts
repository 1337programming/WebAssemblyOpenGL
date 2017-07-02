import { async, ComponentFixture, TestBed } from '@angular/core/testing';

import { WasmComponent } from './wasm.component';

describe('WasmComponent', () => {
  let component: WasmComponent;
  let fixture: ComponentFixture<WasmComponent>;

  beforeEach(async(() => {
    TestBed.configureTestingModule({
      declarations: [ WasmComponent ]
    })
    .compileComponents();
  }));

  beforeEach(() => {
    fixture = TestBed.createComponent(WasmComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should be created', () => {
    expect(component).toBeTruthy();
  });
});
