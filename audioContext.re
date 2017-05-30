module type AudioContextStateType = {
  type t;

  let suspended : t;
  let running : t;
  let closed : t;
};

module AudioContextState: AudioContextStateType = {
  type t = string;

  let suspended : t = "suspended";
  let running : t = "running";
  let closed : t = "closed";
};

module rec AudioContext: {
  /* https://developer.mozilla.org/en-US/docs/Web/API/AudioDestinationNode */
  type destination;

  /* https://developer.mozilla.org/en-US/docs/Web/API/AudioListener */
  type listener;

  type state = AudioContextState.t;

  /* https://developer.mozilla.org/en-US/docs/Web/API/AudioContext */
  type t = Js.t {
    .
    currentTime : float,
    destination : destination,
    listener: listener,
    sampleRate : float,
    state: state,
    /* onstatechange [@bs.meth] : AudioContextStateChangeEvent => unit */

    /* all `EventTarget` stuff
       addEventListener
       removeEventListener
       dispatchEvent
       + */
    close [@bs.meth] : unit => unit,
    createBuffer [@bs.meth] : int => int => float => AudioBuffer.t,
    createConstantSource [@bs.meth] : unit => ConstantSourceNode.t,
    createBufferSource [@bs.meth] : unit => AudioBufferSourceNode.t
    /*
    createMediaElementSource [@bs.meth] : unit => MediaElementAudioSourceNode.t,
    createMediaStreamSource [@bs.meth] : unit => MediaStreamAudioSourceNode.t,
    createMediaStreamDestination [@bs.meth] : unit => MediaStreamAudioDestinationNode.t,
    createScriptProcessor [@bs.meth] : unit => ScriptProcessorNode.t,
    createStereoPanner [@bs.meth] : unit => StereoPannerNode.t,
    createAnalyser [@bs.meth] : unit => AnalyserNode.t,
    createBiquadFilter [@bs.meth] : unit => BiquadFilterNode.t,
    createChannelMerger [@bs.meth] : unit => ChannelMergerNode.t,
    createChannelSplitter [@bs.meth] : unit => ChannelSplitterNode.t,
    createConvolver [@bs.meth] : unit => ConvolverNode.t,
    createDelay [@bs.meth] : unit => DelayNode.t,
    createDynamicsCompressor [@bs.meth] : unit => DynamicsCompressorNode.t,
    createGain [@bs.meth] : unit => GainNode.t,
    createIIRFilter [@bs.meth] : unit => IIRFilterNode.t,
    createOscillator [@bs.meth] : unit => OscillatorNode.t,
    createPanner [@bs.meth] : unit => PannerNode.t,
    createPeriodicWave [@bs.meth] : unit => PeriodicWave.t,
    createWaveShaper [@bs.meth] : unit => WaveShaperNode.t,

    https://developer.mozilla.org/en-US/docs/Web/API/AudioContext/decodeAudioData
    decodeAudioData [@bs.meth] : unit => unit,
    resume [@bs.meth] : unit => unit,
    suspend [@bs.meth] : unit => unit,
    */
  };

  external make : unit => t = "window.AudioContext" [@@bs.new];
} = AudioContext
and AudioBuffer: {
  type channel = int;
  type t = Js.t {
    .
    sampleRate : float,
    length: int,
    duration: float,
    numberOfChannels: int,

    getChannelData [@bs.meth]: Js_typed_array.Float32Array.t => channel => Js_typed_array.Float32Array.t,
    copyFromChannel [@bs.meth]: Js_typed_array.Float32Array.t => channel => int => unit,
    copyToChannel [@bs.meth]: Js_typed_array.Float32Array.t => channel => int => unit
  };
} = AudioBuffer
and AudioBufferSourceNode: {
  type t;

  external connect : t => AudioContext.destination => unit = "connect" [@@bs.send];
  external setBuffer : t => AudioBuffer.t => unit = "buffer" [@@bs.set];
  external start : t => float => unit = "start" [@@bs.send];
  external stop : t => float => unit = "stop" [@@bs.send];
} = AudioBufferSourceNode
and ConstantSourceNode: {
  /* https://developer.mozilla.org/en-US/docs/Web/API/ConstantSourceNode */
  type t;
} = ConstantSourceNode;

/*
https://developer.mozilla.org/en-US/docs/Web/API/MediaElementAudioSourceNode
https://developer.mozilla.org/en-US/docs/Web/API/MediaStreamAudioSourceNode
https://developer.mozilla.org/en-US/docs/Web/API/MediaStreamAudioDestinationNode
https://developer.mozilla.org/en-US/docs/Web/API/ScriptProcessorNode
https://developer.mozilla.org/en-US/docs/Web/API/StereoPannerNode
https://developer.mozilla.org/en-US/docs/Web/API/AnalyserNode
https://developer.mozilla.org/en-US/docs/Web/API/BiquadFilterNode
https://developer.mozilla.org/en-US/docs/Web/API/ChannelMergerNode
https://developer.mozilla.org/en-US/docs/Web/API/ChannelSplitterNode
https://developer.mozilla.org/en-US/docs/Web/API/ConvolverNode
https://developer.mozilla.org/en-US/docs/Web/API/DelayNode
https://developer.mozilla.org/en-US/docs/Web/API/DynamicsCompressorNode
https://developer.mozilla.org/en-US/docs/Web/API/GainNode
https://developer.mozilla.org/en-US/docs/Web/API/IIRFilterNode
https://developer.mozilla.org/en-US/docs/Web/API/OscillatorNode
https://developer.mozilla.org/en-US/docs/Web/API/PannerNode
https://developer.mozilla.org/en-US/docs/Web/API/PeriodicWave
https://developer.mozilla.org/en-US/docs/Web/API/WaveShaperNode
*/
