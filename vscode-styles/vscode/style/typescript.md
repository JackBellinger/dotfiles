# TypeScript and linting

## General

  * `strict` types; avoid `any` and `unknown` unless justified.
  * Use `satisfies` and generics for precise types; prefer `as const` for literals.
  * Organized imports: side‑effect imports first, then external, then internal `@/`.
  * Use path alias `@/` for `src/`.

## ESLint & Prettier

  * Use `@typescript-eslint`, `eslint-plugin-import`, `eslint-plugin-astro`, `eslint-plugin-svelte`.
  * Enforce import order and no unused vars/imports.
  * Prettier is the source of truth for formatting, including Svelte/Astro plugins.

## Errors

  * Narrow errors; never swallow. Wrap external calls and rethrow with context.
  * Prefer `Result`-like patterns or tagged unions over exceptions for domain errors.
