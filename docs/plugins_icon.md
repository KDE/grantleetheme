# Plugins: icon {#plugins_icon}

This plugin introduces a new template tag `icon`. The tag allows easilly displaying
standard icons in the templates by using XDG icon names. The behaviour is identical
to resolving icon path via KIconLoader::iconPath() and passing the path to the
template as a string.

The `icon` tag supports up to three arguments:

    {% icon ICON_NAME [SIZE_OR_GROUP] [ALT_TEXT] %}

* *ICON_NAME* is the name of the icon you would normally pass to QIcon::fromTheme()
  to get the icon. The name can be a string or a name of a context variable holding
  the string. This argument is mandatory.
* *SIZE_OR_GROUP* can either be requested icon size in pixels, or one of the keywords
  `desktop`, `toolbar`, `maintoolbar`, `small`, `panel`, `dialog`, `sizesmall`, `sizesmallmedium`,
  `sizemedium`, `sizelarge`, `sizehuge` or `sizeenormous`. Those strings map to values
  in KIconLoader::Group and KIconLoader::StdSizes enumerators. This argument is optional,
  the default value is `small`.
* *ALT_TEXT* A string to be used as an alt text for the image in the generated HTML code.
   The string must be wrapped in localizer function (`_("Some string")`) or can be
   a name of a context variable holding the string. This argument is optional.
   
## Examples

Show an icon called "kontact", size medium, no alt text:

    {% icon kontact }

Show an icon called "kontact", size small, alt text in variable `kontact_icon_alt`:

    {% icon kontact kontact_icon_alt }

Show an icon called "edit-redo", size medium, alt text "Redo" (localized):

    {% icon edit-redo medium _("Redo") }

Show an icon as specified in `button.icon` context variable, size small, alt test specified in
`button.label` context variable:

    {% icon button.icon small button.label }

