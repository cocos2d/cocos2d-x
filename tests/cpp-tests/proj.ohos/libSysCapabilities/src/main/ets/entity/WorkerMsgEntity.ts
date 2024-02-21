export class ViewRect {
  x: number
  y: number
  w: number
  h: number

  constructor(x: number, y: number, w: number, h: number) {
    this.x = x;
    this.y = y;
    this.w = w;
    this.h = h;
  }
}

export class Color4B {
  r: number
  g: number
  b: number
  a: number

  constructor(r: number, g: number, b: number, a: number) {
    this.r = r;
    this.g = g;
    this.b = b;
    this.a = a;
  }
}

export class BaseWorkerMsgEntity {
  module: string;

  function: string;

  constructor(module: string, func: string) {
    this.module = module;
    this.function = func;
  }
}

export class DialogMsgEntity extends BaseWorkerMsgEntity {
  title: string;

  message: string;

  constructor(module: string, func: string) {
    super(module, func);
  }
}

export class EditBoxMsgEntity extends BaseWorkerMsgEntity {
  viewTag: number

  viewRect: ViewRect

  paddingW: number
  paddingH: number

  visible: boolean

  text: string
  fontSize: number
  color: Color4B
  fontPath: string

  placeHolderText: string
  placeHolderSize: number
  placeHolderColor: Color4B
  placeHolderFontPath: string

  maxLength: number

  inputMode: number

  inputFlag: number

  constructor(module: string, func: string, viewTag?: number) {
    super(module, func);
    this.viewTag = viewTag;
  }
}

export class VideoPlayMsgEntity extends BaseWorkerMsgEntity {
  viewTag: number

  url: string
  isUrl: number

  isLoop: boolean

  viewRect: ViewRect

  visible: boolean

  isFullScreen: boolean

  seekTo: number

  keepAspectRatioEnabled: boolean

  constructor(module: string, func: string, viewTag: number) {
    super(module, func);
    this.viewTag = viewTag;
  }
}

export class WebViewMsgEntity extends BaseWorkerMsgEntity {
  viewTag: number

  data: string
  mimeType: string
  encoding: string
  baseURL: string

  url: string

  filePath: string

  viewRect: ViewRect

  visible: boolean

  opacity: number

  js: string

  scalesPageToFit: boolean

  constructor(module: string, func: string, viewTag: number) {
    super(module, func);
    this.viewTag = viewTag;
  }
}

export class JumpMsgEntity extends BaseWorkerMsgEntity {
  url: string;

  constructor(module: string, func: string) {
    super(module, func);
  }
}