
# Markdown Style Guide

This document outlines my preferred markdown syntax and formatting conventions. Please adhere to these guidelines meticulously when generating markdown content to ensure optimal results. This template focuses solely on structural and stylistic elements, not content.

## 1. General Formatting & Readability

### Line Length

- **paragraphs** Paragraphs should be contained on one line. Separate distinct ideas by a line break.
- **lists** bullet / unordered lists should be one line per bullet / list item

### Blank Line

- **spacing** Use a single blank line to separate paragraphs
- **headers** always include a blank line before a header
- **semantic** Use 2 blank lines to separate distinct logical blocks (e.g., between a heading and the following paragraph, or between different list items if they contain multiple paragraphs/blocks).
- No blank lines directly after an opening list item marker or directly before a closing list item marker.

### Indentation

- **spaces** Use 2 spaces for indentation
- **alignment** use spaces for alignment of tables and chained method calls in code blocks
- **when** only indent
  - nested lists
  - code blocks
  - paragraphs, blockquotes, etc within a list

### Trailing Whitespace

- No trailing whitespace at the end of lines.

### File Encoding

UTF-8
Use simple ASCII characters when possible. Don't use unicode versions of a character that exists in ASCII.
- use -> not →
- use " not ”

## 2. Headings

The document should **always** start with an `# H1`. Use H1 for very distinct ideas, things that could be their own documents. Similar to a class in Java, you can have more than one per file but it should be distinct section and only use multiple when there is good reason.

### Style

Use Atx-style headings only (e.g., `# Heading 1`, `## Heading 2`).

### Spacing

- **symbol** One space between the `#` symbols and the heading text.
- **length** Only use a few words for a heading, no long sentences on the same line.
- A single blank line before each heading (except for the very first heading in a document).
- don't use more than H3
- All headers need one blank line above and below

### Case

- Sentence case for all headings (only the first word and proper nouns capitalized).

## 3. Paragraphs

### Wrapping

Wrap paragraphs at the specified line length (80-100 characters).

### Spacing

Separate paragraphs with a single blank line.

## 4. Lists

### 4.1. Unordered Lists

- **Length** Bullet points should not be more than 1 line long.
  - neither rendered or unrendered views
  - if more explanation is needed use sub-bullets (indented)
- **Marker** Use `-` (dash) as the unordered list item marker.
- **Indentation**
  - all lists need to be indented by 2 spaces.
  - Nested list items should be firther indented with 2 spaces.
  - Content within a list item (e.g., a paragraph, code block) that wraps to a new line should be indented to align with the start of the list item text.
- **Spacing** No blank lines between simple list items.
- **Style:** Only capitalize & use punctuation in a bullet point if it's a full sentence.

### 4.2. Ordered Lists

**Marker:** Use `1.` followed by 2 spaces for all ordered list items.
**Spacing:** No blank lines between simple list items
- Use blank lines between list items only if a list item contains multiple paragraphs or block-level elements.

## 5. Code

### 5.1. Inline Code

- **Delimiters:** Use single backticks (`) for inline code.
- **Spacing:** A single space should precede and follow the inline code block unless it's adjacent to punctuation.

### 5.2. Code Blocks

- **Delimiters:** Use fenced code blocks (triple backticks ```` `) for all code blocks.
- **Language Specification:** Always specify the language immediately after the opening triple backticks (e.g., `` ```python ``).
- **Indentation:** No extra indentation for the fenced code block itself. The code *within* the block should follow its own language's standard indentation.
- **Blank Lines:** A single blank line before and after a code block.

## 6. Blockquotes

- **Marker:** Use `>` followed by a single space for blockquote markers.
- **Nesting:** Indent nested blockquotes further with `> >`.
- **Spacing:** A single blank line before and after a blockquote.

## 7. Emphasis

- **Bold:** Use double asterisks (`**bold**`).
- **Italic:** Use single asterisks (`*italic*`).
- Use bolded text sparingly. in cases such as:
  - **lists:** to separate a category from the rest of the line in a bullet point
  - to give **emphasis** to a word or phrase that is highly important.

## 8. Links

- **Style:** Use inline link style whenever possible (e.g., `[link text](URL)`).
- **Reference Links:** Use reference-style links only for very long URLs or when the same URL is used multiple times (e.g., `[link text][id]` with `[id]: URL` at the bottom).
- **Spacing:** No extra spaces inside the link `[]` or `()`.

## 9. Images

- **Style:** Use inline image style whenever possible (e.g., `![alt text](URL "title text")`).
- **Spacing:** No extra spaces inside the image `[]` or `()`.
- **Alt Text:** Always provide descriptive alt text.

## 10. Tables

- **Syntax:** Use standard GitHub Flavored Markdown table syntax.
- **Alignment:** Use colons within the header separator line (`---`) to specify column alignment (`:` for left, `:` on both ends for center, `:` for right).
- **Pipes:** Ensure consistent use of pipes (`|`) for column separation.
- **Spacing:** A single blank line before and after a table.
- **Style:** Tables should be legible and aligned even in the unrendered markdown.

## 11. Horizontal Rules

- **Marker:** Use three asterisks (`***`) on a line by themselves.
- **Spacing:** A single blank line before and after a horizontal rule.

## 12. Miscellaneous

- **Comments:** Markdown does not natively support comments.
- **Special Characters:** Escape special markdown characters (e.g., `\*`, `\_`, `\#`) with a backslash if they are meant to be literal characters rather than markdown syntax.
- **File Naming:** Use lowercase, hyphen-separated file names (kebab-case).

## Markdown lint rules

```json
"markdownlint.config": {
        // All rules explicitly listed with typical/default settings.
        // Edit any entry to enable/disable or change options.
        // Rules are keyed by their MD### identifier.

        "MD001": true, // heading levels should only increment by one level at a time
        "MD002": true, // first heading should be a top level heading
        "MD003": { "style": "consistent" }, // heading style
        "MD004": { "style": "consistent" }, // unordered list style
        "MD005": true, // inconsistent indentation for list items at the same level
        "MD006": { "style": "consistent" }, // bland list marker usage
        "MD007": { "indent": 2, "start_indent": 2, "start_indented": true}, // unordered list indentation
        "MD008": { "space": 1 }, // no trailing spaces
        "MD009": true, // no trailing spaces (alias / similar)
        "MD010": false, // no hard tabs
        "MD011": true, // no inline HTML
        "MD012": true, // multiple consecutive blank lines
        "MD013": { "line_length": 1000, "tables": true, "code_blocks": true }, // line length
        "MD014": true, // dollar signs used before commands without showing output
        "MD015": true, // horizontal rule style
        "MD016": true, // hanging punctuation in headings
        "MD017": true, // no space after hash in headers
        "MD018": true, // no space after hash on atx header
        "MD019": true, // no multiple spaces after hash on atx header
        "MD020": true, // no missing space after hash atx header
        "MD021": true, // no duplicate headings
        "MD022": false, // headings should be surrounded by blank lines
        "MD023": true, // headings must be surrounded by blank lines (alternate)
        "MD024": false, // multiple headings with same content
        "MD025": true, // single top level heading in the document
        "MD026": true, // trailing punctuation in heading
        "MD027": true, // multiple spaces after blockquote symbol
        "MD028": true, // blank line inside blockquote
        "MD029": { "style": "ordered" }, // ordered list item prefix
        "MD030": { "ul_single": 1, "ol_single": 2, "ol_multi": 2, "ul_multi": 1 }, // spaces after list markers (default tolerant)
        "MD031": false, // fenced code blocks should be surrounded by blank lines
        "MD032": false, // lists should be surrounded by blank lines
        "MD033": { "allowed_elements": [] }, // inline HTML (empty = disallow)
        "MD034": true, // bare URL used
        "MD035": { "style": "---" }, // horizontal rule style (default '---')
        "MD036": false, // emphasis used instead of heading
        "MD037": true, // spaces inside emphasis markers
        "MD038": true, // spaces inside code span elements
        "MD039": true, // spaces inside link text
        "MD040": true, // fenced code blocks should have a language specified
        "MD041": true, // first line should be a top level heading
        "MD042": true, // no empty links
        "MD043": true, // required heading levels in a document (if used)
        "MD044": true, // proper names (extension-specific)
        "MD045": true, // consistent emphasis character
        "MD046": true, // code block style
        "MD047": true, // files should end with a single newline
        "MD048": true, // code fence style

        // Extra/behavioral settings (commonly used by markdownlint CLI / extension)
        // They are included here so you can tweak them in one place.
        "default": true,
        "files": ["**/*.md", "**/*.markdown"],

        // NOTE: If you want a rule disabled, set it to false:
        // e.g. "MD013": false
        // Or to customize a rule, change the value/object above.
        //
        // This block is intentionally explicit so you can see and edit
        // every rule quickly. If a rule is missing from this list,
        // markdownlint will fall back to its own internal default.
        //
        // End of markdownlint.config
    },
```
