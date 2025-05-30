--- @meta

-- This file is autogenerated. Do not edit this file manually. Your changes will be ignored.
-- More information: https://github.com/MWSE/MWSE/tree/master/docs

--- A texture that is also a render target. This object can be used with niRenderer:setRenderTarget and rendered into. It can be directly used in a texturing property, or read back into system memory (at a performance cost). After using it as a render target, make sure you reset the renderer with niRenderer:setRenderTarget(nil) so that it's not bound as a source texture and a target at the same time.
--- @class niRenderedTexture : niTexture, niObjectNET, niObject
--- @field readback boolean Reads the contents of the rendered texture into a system memory niPixelData. This requires that the rendered texture is not the current render target -- make sure niRenderer:setRenderTarget(nil) is called before using this function. The texture dimensions of the niRenderedTexture and niPixelData must be the same. It returns true if the readback succeeded, false otherwise.
--- 	
--- This function requires the GPU to finish rendering and send data to the CPU. This can impact framerates significantly, so measure and consider performance carefully when using this.
niRenderedTexture = {}

--- Creates an niRenderedTexture.
--- @param width number The width of the rendered texture. Should be a power of 2.
--- @param height number The height of the rendered texture. Should be a power of 2.
--- @return niRenderedTexture texture No description yet available.
function niRenderedTexture.create(width, height) end

