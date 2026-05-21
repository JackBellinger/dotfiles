# Astro style guide

Astro is our primary site framework. Prefer `.astro` for pages and layouts; use `.svelte` for interactive islands.

## Pages and layouts

	* Put top-level routes in `src/pages/`.
	* Use layouts in `src/layouts/` to centralize scaffolding (head/meta, header/footer).
	* Prefer server rendering or static generation as appropriate; avoid client JS by default.
	* Co-locate page-specific styles inside the `.astro` file.

## Content collections

	* Define schemas in `src/content.config.ts` with `zod`.
	* Required frontmatter: `title`, `description`, `pubDate`, `tags`, `draft`.
	* Generate slugs consistently; avoid hard-coded links to file paths.
	* Fetch content via `getCollection` and pass typed data to components.

## Images and assets

	* Use `astro:assets` and `<Image />` for responsive images.
	* Always include meaningful `alt` text.
	* Optimize sizes; avoid remote images unless necessary.

## SEO and head

	* Set canonical URLs, meta description, and Open Graph/Twitter tags in layouts.
	* Provide structured data when relevant.

## Accessibility

	* Semantic headings (no skipping levels).
	* Links must have descriptive text (no "here").
	* Ensure color contrast and keyboard navigation.
