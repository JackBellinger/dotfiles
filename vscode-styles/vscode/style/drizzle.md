# Drizzle ORM and migrations

## Schema conventions

  * Use snake_case for table and column names; singular table names or clarify choice.
  * Primary keys: `id` bigint/UUID; timestamps: `created_at`, `updated_at` (UTC).
  * Name FKs as `<table>_id`; enforce referential actions.

## Migrations

  * One logical change per migration; descriptive filenames.
  * Review migrations in PR; include rollback notes.
  * Post-process scripts go in `scripts/` and are idempotent.

## Validation and access

  * Validate inputs with `zod`; never trust request payloads.
  * Encapsulate queries in repository functions; avoid inline SQL scattered across code.
