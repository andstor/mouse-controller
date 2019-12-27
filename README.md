# mouse-controller

> Node.js C++ Addon for controlling mouse behavior

[![Build Status](https://travis-ci.org/andstor/mouse-controller.svg?branch=master)](https://travis-ci.org/andstor/mouse-controller)
[![Coverage Status](https://coveralls.io/repos/github/andstor/mouse-controller/badge.svg?branch=master)](https://coveralls.io/github/andstor/mouse-controller?branch=master)
[![npm version](http://img.shields.io/npm/v/mouse-controller.svg?style=flat)](https://npmjs.org/package/mouse-controller "View this project on npm")

## Table of Contents
  * [Supported Plattforms](#supported-plattforms)
  * [Installation](#installation)
  * [Usage](#usage)
  * [Methods](#methods)
  * [Build instrictions](#build-instructions)

## Supported Plattforms

Currently supported plattforms are:

- **MacOS**

## Installation

```sh
$ npm install --save mouse-controller
```

[Precompiled binaries](https://github.com/andstor/mouse-controller/releases/latest) for popular 64-bit platforms are provided. When installing `mouse-controller`, [`node-pre-gyp`](https://github.com/mapbox/node-pre-gyp) will check if a compatible binary exists and fallback to a compile step if it doesn't. In that case you'll need a [valid `node-gyp` installation](https://github.com/nodejs/node-gyp#installation).

If you don't want to use the prebuilt binary for the platform you are installing on, specify the `--build-from-source` flag when you install. One of:

```
npm install --build-from-source
npm install mouse-controller --build-from-source
```


## Usage

### Syntax
```js
new MouseController()
```

### Example
```js
const MouseController = require('mouse-controller');
const mc = new MouseController();

console.log(mc.getPosition());
//=> { x: 143.9375, y: 129.0625 }

// Move the mouse to the coordinates (500, 500).
mc.move(500, 500);

// Right click at the current mouse position.
mc.click(mc.BUTTON.RIGHT, mc.getPosition());
```

## Constants

### BUTTON
Constant for specifying the mouse button type.

| Constant | Value | Button             |
| :------- | :---: | :----------------- |
| `LEFT`   |  `0`  | Left mouse button  |
| `RIGHT`  |  `1`  | Right mouse button |

## Methods

### move(x, y)
- **x**:
  - Type: `Number`
  - x-coordinate for the new mouse position.

- **y**:
  - Type: `Number`
  - y-coordinate for the new mouse position.

Moves the mouse to the point (`x`, `y`).

### click(BUTTON, point)
- **BUTTON**:
  - Type: [`BUTTON`](#button)
  - Which mouse button to click. The [`BUTTON`](#button) type is defined as multiple constants.

- **point**:
  - Type: `Object`
  - Which mouse button to click.

Clicks with the `BUTTON` at the `point` provided. To click in the corrent position of the mouse, use the method [getPosition()](#getPosition).

### doubleClick(BUTTON, point)
- **BUTTON**:
  - Type: [`BUTTON`](#button)
  - Which mouse button to click. The [`BUTTON`](#button) type is defined as multiple constants on the BUTTON object.

- **point**:
  - Type: `Object`
  - Which mouse button to click.

Double clicks with the `BUTTON` at the `point` provided. To click in the corrent position of the mouse, use the method [getPosition()](#getPosition).

### getPosition()
- (return value):
  - Type: `Object`
  - Returns the current mouse position.

Gets the current mouse position on the form `{ x: 143.9375, y: 129.0625 }`.

### startDrag(point)
- **point**:
  - Type: `Object`
  - Object with `x` and `y` coordinates of the vanted mouse position to start the mouse drag from.

Start to drag by pressing down on the left mouse button at the point (`x`, `y`). To do consecutive movement while dragging, use the [drag(point)](#dragpoint) method.

### drag(point)
- **point**:
  - Type: `Object`
  - Object with `x` and `y` coordinates of the vanted mouse position to end the mouse drag on.

To move the mouse that is activly dragging,  the point (`x`, `y`).

### endDrag(point)
- **point**:
  - Type: `Object`
  - Object with `x` and `y` coordinates of the vanted mouse position to end the mouse drag on.

End a mouse drag by releasing the left mouse button at the point (`x`, `y`).
