# Svelte style guide

Use `.svelte` for interactive islands mounted from `.astro` pages. Keep components small and focused.

## Components

  * Name components in `PascalCase.svelte`.
  * Props must be typed; avoid `any`. Export minimal public API.
  * Prefer slots over many boolean props; document slot expectations.
  * Emit events as `createEventDispatcher()` with kebab-case names.

## Stores and state

  * Use local component state first; elevate to stores only when shared.
  * Use `readable/writable/derived` from `svelte/store`; strongly type them.
  * Unsubscribe in `onDestroy` when subscribing manually.

## Accessibility

  * Label controls, manage focus, ensure keyboard navigation.
  * Use semantic elements before `role`.

## Styling

  * Prefer component-scoped styles. Keep global styles in `src/styles/global.css`.
  * Avoid deep selectors; compose with utility classes when possible.
