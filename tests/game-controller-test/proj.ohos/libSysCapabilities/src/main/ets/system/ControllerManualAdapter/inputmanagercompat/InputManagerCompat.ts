interface  InputManagerCompat {
  getInputDevice(id);

  getInputDeviceIds(): [];

  registerInputDeviceListener(listener: InputDeviceListener, handler);

  unregisterInputDeviceListener(listener: InputDeviceListener);

  onGenericMotionEvent(event);

  onPause();

  onResume();

}

interface InputDeviceListener {
  onInputDeviceAdded(deviceId);

  onInputDeviceChanged(deviceId);

  onInputDeviceRemoved(deviceId);
}

class Factory {
  getInputManager(context) {

  }
}