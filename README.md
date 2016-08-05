# GrantleeTheme

GrantleeTheme library provides a class for loading theme packages containing
set of templates.

## Template syntax

The library provides a KDE-specific Grantlee plugins that introduce
new tags into the Grantlee theme syntax:

* [Icons](@ref plugins_icon)

## Localization

The library provides GrantleeKI18nLocalizer, a Grantlee::AbstractLocalizer
subclass that integrates with Ki18n (the KDE localization framework) instead
of the Qt localization system.

## Qt Resource System support

Grantlee only supports loading templates from files on disk currently.
The GrantleeTheme library provides QtResourceTemplateLoader, which
allows loading Grantlee templates from the Qt Resource System.
