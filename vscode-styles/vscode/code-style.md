# Coding style and architecture (index)

Our stack: Astro + Svelte islands, Cloudflare Workers, Drizzle ORM, Vitest.

Philosophy: framework-oriented, readable, maintainable, refactorable. Prefer conventions over configuration and eliminate boilerplate by design.

## Use the right guide

	* Astro: `.vscode/style/astro.md`
	* Svelte: `.vscode/style/svelte.md`
	* TypeScript & linting: `.vscode/style/typescript.md`
	* Cloudflare Workers: `.vscode/style/cloudflare-workers.md`
	* Drizzle ORM & migrations: `.vscode/style/drizzle.md`
	* Testing (Vitest): `.vscode/style/testing.md`
	* Logging & observability: `.vscode/style/logging.md`

## Conventions snapshot

	* Type-first code; strict TS; no implicit `any`.
	* `.astro` for pages/layouts; `.svelte` only for interactivity.
	* Content via content collections with zod schemas; use `<Image />` and alt text.
	* Workers return typed `Response` and structured JSON errors; cache prudently.
	* Drizzle: clear schema naming, reviewed migrations, validate with zod.
	* Tests: unit + integration; mock Workers env; minimal snapshots.
	* Logs: structured with `requestId`; redact secrets.

