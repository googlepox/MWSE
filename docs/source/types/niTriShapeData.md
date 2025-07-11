# niTriShapeData
<div class="search_terms" style="display: none">nitrishapedata, trishapedata</div>

<!---
	This file is autogenerated. Do not edit this file manually. Your changes will be ignored.
	More information: https://github.com/MWSE/MWSE/tree/master/docs
-->

Contains the geometry data for an `NiTriShape` object.

This type inherits the following: [niTriBasedGeometryData](../types/niTriBasedGeometryData.md), [niGeometryData](../types/niGeometryData.md), [niObject](../types/niObject.md).
## Properties

### `activeTriangleCount`
<div class="search_terms" style="display: none">activetrianglecount</div>

The active triangle count of the object.

**Returns**:

* `result` (number)

***

### `bounds`
<div class="search_terms" style="display: none">bounds</div>

The model-space bounding sphere of the object.

**Returns**:

* `result` ([niBound](../types/niBound.md))

***

### `colors`
<div class="search_terms" style="display: none">colors</div>

*Read-only*. The vertex colors for the object. The length of the array is equal to `vertexCount`.

**Returns**:

* `result` ([niPackedColor](../types/niPackedColor.md)[])

***

### `normals`
<div class="search_terms" style="display: none">normals</div>

*Read-only*. The list of unitized, model-space vertex normals for the object. The length of the array is equal to `vertexCount`.

**Returns**:

* `result` ([tes3vector3](../types/tes3vector3.md)[])

***

### `refCount`
<div class="search_terms" style="display: none">refcount</div>

*Read-only*. The number of references that exist for this object. When this value reaches zero, the object will be deleted.

**Returns**:

* `result` (number)

***

### `RTTI`
<div class="search_terms" style="display: none">rtti</div>

*Read-only*. The runtime type information for this object. This is an alias for the `.runTimeTypeInformation` property.

**Returns**:

* `result` ([niRTTI](../types/niRTTI.md))

***

### `runTimeTypeInformation`
<div class="search_terms" style="display: none">runtimetypeinformation</div>

*Read-only*. The runtime type information for this object.

**Returns**:

* `result` ([niRTTI](../types/niRTTI.md))

***

### `texCoords`
<div class="search_terms" style="display: none">texcoords</div>

*Read-only*. The array of texture coordinates. The length of the array is equal to `vertexCount` times `textureSets`.

**Returns**:

* `result` ([tes3vector2](../types/tes3vector2.md)[])

***

### `textures`
<div class="search_terms" style="display: none">textures</div>

*Read-only*. The array of texture coordinates. The length of the array is equal to `vertexCount` times `textureSets`.

**Returns**:

* `result` ([tes3vector2](../types/tes3vector2.md)[])

***

### `textureSets`
<div class="search_terms" style="display: none">texturesets</div>

The number of texture coordinate sets in the data.

**Returns**:

* `result` (number)

***

### `triangleCount`
<div class="search_terms" style="display: none">trianglecount</div>

*Read-only*. The triangle count of the object.

**Returns**:

* `result` (number)

***

### `triangles`
<div class="search_terms" style="display: none">triangles</div>

The access to the triangles of the object. The length of the array is equal to the number of active triangles.

**Returns**:

* `result` ([niTriangle](../types/niTriangle.md)[])

***

### `uniqueID`
<div class="search_terms" style="display: none">uniqueid</div>

*Read-only*. A unique ID for this model, assigned at model creation.

**Returns**:

* `result` (number)

***

### `vertexCount`
<div class="search_terms" style="display: none">vertexcount</div>

*Read-only*. The vertex count for the object.

**Returns**:

* `result` (number)

***

### `vertices`
<div class="search_terms" style="display: none">vertices</div>

*Read-only*. The array of vertex position data. The length of the array is equal to `vertexCount`.

**Returns**:

* `result` ([tes3vector3](../types/tes3vector3.md)[])

***

## Methods

### `clone`
<div class="search_terms" style="display: none">clone</div>

Creates a copy of this object.

```lua
local result = myObject:clone()
```

**Returns**:

* `result` ([niObject](../types/niObject.md))

***

### `copy`
<div class="search_terms" style="display: none">copy</div>

Creates a copy of the data. An optional table of filters can be passed to remove information from the copy.

```lua
local copiedData = myObject:copy({ normals = ..., colors = ..., texCoords = ... })
```

**Parameters**:

* `filters` (table): *Optional*.
	* `normals` (boolean): *Default*: `true`. If false, the geometry data's normals will be absent from the copy.
	* `colors` (boolean): *Default*: `true`. If false, the geometry data's colors will be absent from the copy.
	* `texCoords` (boolean): *Default*: `true`. If false, the geometry data's texture coordinates will be absent from the copy.

**Returns**:

* `copiedData` ([niTriShapeData](../types/niTriShapeData.md)): The duplicated data.

***

### `isInstanceOfType`
<div class="search_terms" style="display: none">isinstanceoftype, instanceoftype</div>

Determines if the object is of a given type, or of a type derived from the given type.

```lua
local result = myObject:isInstanceOfType(type)
```

**Parameters**:

* `type` ([ni.type](../references/ni/types.md)): Use values in the [`ni.type`](https://mwse.github.io/MWSE/references/ni/types/) table.

**Returns**:

* `result` (boolean)

***

### `isOfType`
<div class="search_terms" style="display: none">isoftype, oftype</div>

Determines if the object is of a given type.

```lua
local result = myObject:isOfType(type)
```

**Parameters**:

* `type` ([ni.type](../references/ni/types.md)): Use values in the [`ni.type`](https://mwse.github.io/MWSE/references/ni/types/) table.

**Returns**:

* `result` (boolean)

***

### `markAsChanged`
<div class="search_terms" style="display: none">markaschanged</div>

Tells the renderer that the object has changed. Should be called after you have finished changing any vertex data.

If you have altered vertex positions, you may need to also call `updateModelBound`. You should call it if vertices have been moved outside the bounds of the original model.

```lua
myObject:markAsChanged()
```

***

### `saveBinary`
<div class="search_terms" style="display: none">savebinary</div>

Serializes the object, and writes it to the given file.

```lua
local success = myObject:saveBinary(path)
```

**Parameters**:

* `path` (string): The path to write the file at, relative to the Morrowind installation folder. The `.nif` extension needs to be specified manually.

**Returns**:

* `success` (boolean): If true the object was successfully serialized.

***

### `updateModelBound`
<div class="search_terms" style="display: none">updatemodelbound, modelbound</div>

Updates the geometry bounds to match the vertex data. You should call it if vertices have been moved outside the bounds of the original model, or if the effective bounds have become significantly smaller. 

If you already know the effective radius of the vertex data, you could more efficiently set the bounds directly instead of calling this function.

```lua
myObject:updateModelBound()
```

