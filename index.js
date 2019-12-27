var binary = require('node-pre-gyp');
var path = require('path')
var binding_path = binary.find(path.resolve(path.join(__dirname, './package.json')));
var binding = require(binding_path);

let MouseController = binding.MouseController;
MouseController.BUTTON = Object.freeze({
  LEFTBUTTON: 0,
  RIGHTBUTTON: 1,
});

module.exports = MouseController;
