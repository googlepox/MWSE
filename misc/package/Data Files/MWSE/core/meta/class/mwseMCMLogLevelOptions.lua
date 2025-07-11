--- @meta

-- This file is autogenerated. Do not edit this file manually. Your changes will be ignored.
-- More information: https://github.com/MWSE/MWSE/tree/master/docs

--- A premade setting to adjust log level setting for your [logger](https://mwse.github.io/MWSE/types/mwseLogger/) with minimal setup. For convenience, it provides default label text and description.
--- @class mwseMCMLogLevelOptions : mwseMCMDropdown, mwseMCMSetting, mwseMCMComponent
mwseMCMLogLevelOptions = {}

--- Creates a new LogLevelOptions setting.
--- @param data? mwseMCMLogLevelOptions.new.data This table accepts the following values:
--- 
--- `label?`: string — *Optional*. The text shown above the dropdown. If not provided, the default label text will be used.
--- 
--- `description?`: string — *Optional*. If in a [Sidebar Page](../types/mwseMCMSideBarPage.md), the description will be shown on mouseover. If not provided, the default description will be used.
--- 
--- `logger?`: mwseLogger|string — *Optional*. A logger whose logging level will be changed. The setting will try to automatically resolve your mod's logger using the same mechanism as `mwse.Logger.new`. If this isn't possible, an error message will be printed to the `MWSE.log`. In such a case, you can pass your mod's logger or mod name.
--- 
--- `options?`: mwseMCMDropdownOption[] — *Optional*. This table holds the text and variable value for each of the dropdown's options.
--- 
--- `variable?`: mwseMCMConfigVariable|mwseMCMCustomVariable|mwseMCMGlobal|mwseMCMGlobalBoolean|mwseMCMPlayerData|mwseMCMTableVariable|mwseMCMVariable|mwseMCMSettingNewVariable — *Optional*. A variable for this setting.
--- 
--- `defaultSetting?`: unknown — *Optional*. If `defaultSetting` wasn't passed in the `variable` table, can be passed here. The new variable will be initialized to this value.
--- 
--- `idleColor?`: number[] — *Default*: `tes3ui.getPalette(tes3.palette.normalColor)`. The idle color for dropdown. Needs to be an RGB trio in the range [0.0, 1.0].
--- 
--- `overColor?`: number[] — *Default*: `tes3ui.getPalette(tes3.palette.normalOverColor)`. The color used when the mouse if hovering over the dropdown. Needs to be an RGB trio in the range [0.0, 1.0].
--- 
--- `pressedColor?`: number[] — *Default*: `tes3ui.getPalette(tes3.palette.normalPressedColor)`. The color used when the dropdown is being pressed. Needs to be an RGB trio in the range [0.0, 1.0].
--- 
--- `callback?`: fun(self: mwseMCMLogLevelOptions) — *Optional*. The custom function called when the player interacts with this Setting.
--- 
--- `inGameOnly?`: boolean — *Default*: `false`. If true, the setting is disabled while the game is on main menu.
--- 
--- `restartRequired?`: boolean — *Default*: `false`. If true, updating this Setting will notify the player to restart the game.
--- 
--- `restartRequiredMessage?`: string — *Optional*. The message shown if restartRequired is triggered. The default text is a localized version of: "The game must be restarted before this change will come into effect."
--- 
--- `indent?`: integer — *Default*: `12`. The left padding size in pixels. Only used if the `childIndent` isn't set on the parent component.
--- 
--- `childIndent?`: integer — *Optional*. The left padding size in pixels. Used on all the child components.
--- 
--- `paddingBottom?`: integer — *Default*: `4`. The bottom border size in pixels. Only used if the `childSpacing` is unset on the parent component.
--- 
--- `childSpacing?`: integer — *Optional*. The bottom border size in pixels. Used on all the child components.
--- 
--- `postCreate?`: fun(self: mwseMCMLogLevelOptions) — *Optional*. Can define a custom formatting function to make adjustments to any element saved in `self.elements`.
--- 
--- `class?`: string — *Optional*. No description yet available.
--- 
--- `componentType?`: string — *Optional*. No description yet available.
--- 
--- `parentComponent?`: mwseMCMActiveInfo|mwseMCMBinder|mwseMCMButton|mwseMCMCategory|mwseMCMColorPicker|mwseMCMColorPickerButton|mwseMCMComponent|mwseMCMCycleButton|mwseMCMDropdown|mwseMCMExclusionsPage|mwseMCMFilterPage|mwseMCMHyperlink|mwseMCMInfo|mwseMCMKeyBinder|mwseMCMLogLevelOptions|mwseMCMMouseBinder|mwseMCMMouseOverInfo|mwseMCMMouseOverPage|mwseMCMOnOffButton|mwseMCMPage|mwseMCMParagraphField|mwseMCMPercentageSlider|mwseMCMSetting|mwseMCMSideBarPage|mwseMCMSideBySideBlock|mwseMCMSlider|mwseMCMTemplate|mwseMCMTextField|mwseMCMYesNoButton — *Optional*. No description yet available.
--- @return mwseMCMLogLevelOptions dropdown No description yet available.
function mwseMCMLogLevelOptions:new(data) end

---Table parameter definitions for `mwseMCMLogLevelOptions.new`.
--- @class mwseMCMLogLevelOptions.new.data
--- @field label? string *Optional*. The text shown above the dropdown. If not provided, the default label text will be used.
--- @field description? string *Optional*. If in a [Sidebar Page](../types/mwseMCMSideBarPage.md), the description will be shown on mouseover. If not provided, the default description will be used.
--- @field logger? mwseLogger|string *Optional*. A logger whose logging level will be changed. The setting will try to automatically resolve your mod's logger using the same mechanism as `mwse.Logger.new`. If this isn't possible, an error message will be printed to the `MWSE.log`. In such a case, you can pass your mod's logger or mod name.
--- @field options? mwseMCMDropdownOption[] *Optional*. This table holds the text and variable value for each of the dropdown's options.
--- @field variable? mwseMCMConfigVariable|mwseMCMCustomVariable|mwseMCMGlobal|mwseMCMGlobalBoolean|mwseMCMPlayerData|mwseMCMTableVariable|mwseMCMVariable|mwseMCMSettingNewVariable *Optional*. A variable for this setting.
--- @field defaultSetting? unknown *Optional*. If `defaultSetting` wasn't passed in the `variable` table, can be passed here. The new variable will be initialized to this value.
--- @field idleColor? number[] *Default*: `tes3ui.getPalette(tes3.palette.normalColor)`. The idle color for dropdown. Needs to be an RGB trio in the range [0.0, 1.0].
--- @field overColor? number[] *Default*: `tes3ui.getPalette(tes3.palette.normalOverColor)`. The color used when the mouse if hovering over the dropdown. Needs to be an RGB trio in the range [0.0, 1.0].
--- @field pressedColor? number[] *Default*: `tes3ui.getPalette(tes3.palette.normalPressedColor)`. The color used when the dropdown is being pressed. Needs to be an RGB trio in the range [0.0, 1.0].
--- @field callback? fun(self: mwseMCMLogLevelOptions) *Optional*. The custom function called when the player interacts with this Setting.
--- @field inGameOnly? boolean *Default*: `false`. If true, the setting is disabled while the game is on main menu.
--- @field restartRequired? boolean *Default*: `false`. If true, updating this Setting will notify the player to restart the game.
--- @field restartRequiredMessage? string *Optional*. The message shown if restartRequired is triggered. The default text is a localized version of: "The game must be restarted before this change will come into effect."
--- @field indent? integer *Default*: `12`. The left padding size in pixels. Only used if the `childIndent` isn't set on the parent component.
--- @field childIndent? integer *Optional*. The left padding size in pixels. Used on all the child components.
--- @field paddingBottom? integer *Default*: `4`. The bottom border size in pixels. Only used if the `childSpacing` is unset on the parent component.
--- @field childSpacing? integer *Optional*. The bottom border size in pixels. Used on all the child components.
--- @field postCreate? fun(self: mwseMCMLogLevelOptions) *Optional*. Can define a custom formatting function to make adjustments to any element saved in `self.elements`.
--- @field class? string *Optional*. No description yet available.
--- @field componentType? string *Optional*. No description yet available.
--- @field parentComponent? mwseMCMActiveInfo|mwseMCMBinder|mwseMCMButton|mwseMCMCategory|mwseMCMColorPicker|mwseMCMColorPickerButton|mwseMCMComponent|mwseMCMCycleButton|mwseMCMDropdown|mwseMCMExclusionsPage|mwseMCMFilterPage|mwseMCMHyperlink|mwseMCMInfo|mwseMCMKeyBinder|mwseMCMLogLevelOptions|mwseMCMMouseBinder|mwseMCMMouseOverInfo|mwseMCMMouseOverPage|mwseMCMOnOffButton|mwseMCMPage|mwseMCMParagraphField|mwseMCMPercentageSlider|mwseMCMSetting|mwseMCMSideBarPage|mwseMCMSideBySideBlock|mwseMCMSlider|mwseMCMTemplate|mwseMCMTextField|mwseMCMYesNoButton *Optional*. No description yet available.

