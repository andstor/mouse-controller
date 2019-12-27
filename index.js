var binary = require('node-pre-gyp');
var path = require('path')
var binding_path = binary.find(path.resolve(path.join(__dirname, './package.json')));
var binding = require(binding_path);

let MouseController = binding.MouseController;
MouseController.prototype.BUTTON = Object.freeze({
  LEFT: 0,
  RIGHT: 1,
});

module.exports = MouseController;
