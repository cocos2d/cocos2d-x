function crashed() {
  // nacl modules send "crashed" when they call exit() and this sample
  // calls exit() when the exit icon is pressed.
  window.close()
}

function addListeners() {
  document.getElementById('nacl_module').addEventListener('crash', crashed, true);
}

document.addEventListener('DOMContentLoaded', addListeners);
