# To-do list

Needed and planned features will be placed into this file.

## [TODO]

Here's what needs to happen before full release.

### Color Editing
- [ ] Copy & paste function
- [ ] Swatch color selector
	- [ ] Recent colors
- [ ] Repeating patterns, like have only 2 selections and the pattern sent is simply those 2 colors repeating
	- [ ] Maybe integrate this into Arduino, if it's sent too few colors, then automatically repeat the pattern

### Palette Sharing
- [ ] Look into file permissions

### Communication
- [ ] When connected to Arduino, immediately ask for version and prompt if app is out of date
	- (Backward compatibility is not necessary as SigmonLED is still in Beta)

### About Page
- [x] Paragraph
- [x] Version string
- [x] Arduino version

### QoL
- [ ] Make prompt for location services if they are disabled (needed for BLE)
- [ ] Make pair button so that location services may not be required
- [ ] Maybe even make renaming functionality so user doesn't need serial adapter
- [x] Fix layout for regular sized phones (use emulators)
- [ ] Replace buttons in toolbar with icons
- [ ] Add icon to about page
- [ ] Make toolbar header respond to dark mode

### Layout
- [x] Fix layout for PaletteForm
- [x] Color view is hidden at top. Move it to bottom and move apply button
- [ ] Make the content/footer design for all pages
