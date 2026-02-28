# GDPlatform - OAuth (Geode Mod)

GD-OAuth is a Mod used to work Authentication Code and API.

## OAuth with GDPlatform API Example Usage

For Example (JavaScript - GDPlatform OAuth):
```js
fetch("https://api--gdplatform.netlify.app/oauth/code", {
  method: "POST",
  body: JSON.stringify({
    code: "ABC123"
  })
});
```

For GDPlatform OAuth: [**See GDPlatform Documentations about how it works with Auth**](https://gdplatform.netlfiy.app/docs)

# How it works this Mod?

You can click the Auth (a Profile Icon) Button to Generate a Verification Code and you can Validate a Code with Official Website. Only works with [Sign In · GDPlatform](https://gdplatform.netlfiy.app/login) or [Create Account · GDPlatform](https://gdplatform.netlfiy.app/register)

The Mod is a part of verification because only works GDPlatform Website Official using Account Sign In or Account Creation.

Geometry Dash OAuth2 is a Provider that allows Developers to use this Provider and GDPlatform API.

Note: This Mod includes GDPlatform API (HTTP Request) for JavaScript, Java, Laravel, PHP and C++. from this geode build is not built on GitHub. The mod is not used for dependency api, it also uses http requests.
