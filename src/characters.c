/*
Date:- 2023-Sep-19:17-05-58 PM
This symbols are Copied from  ( Copyright (C) 2018-2022 Hans Petter Jansson)
    https://github.com/hpjansson/chafa/blob/153d8cca95ff02fc42681d47cdb84eec779a9499/tools/chafa/c64-platform.c
            and
    https://github.com/hpjansson/chafa/blob/153d8cca95ff02fc42681d47cdb84eec779a9499/tools/chafa/ibm-platform.c

*/


typedef struct CodeMap
{
    gint c;
    gunichar u;
}
CodeMap;


static const CodeMap normal [] =
{
    /* 0-127 */
    { 0, '@' },
    { 1, 'A' },
    { 2, 'B' },
    { 3, 'C' },
    { 4, 'D' },
    { 5, 'E' },
    { 6, 'F' },
    { 7, 'G' },
    { 8, 'H' },
    { 9, 'I' },
    { 10, 'J' },
    { 11, 'K' },
    { 12, 'L' },
    { 13, 'M' },
    { 14, 'N' },
    { 15, 'O' },
    { 16, 'P' },
    { 17, 'Q' },
    { 18, 'R' },
    { 19, 'S' },
    { 20, 'T' },
    { 21, 'U' },
    { 22, 'V' },
    { 23, 'W' },
    { 24, 'X' },
    { 25, 'Y' },
    { 26, 'Z' },
    { 27, '[' },
    { 28, 0xa3 }, /* £ pound symbol*/
    { 29, ']' },
    { 30, 0x2191 }, /* ↑ up arrow */
    { 31, 0x2190 }, /* ← left arrow */
    { 32, ' ' },
    { 33, '!' },
    { 34, '"' },
    { 35, '#' },
    { 36, '$' },
    { 37, '%' },
    { 38, '&' },
    { 39, '\'' },
    { 40, '(' },
    { 41, ')' },
    { 42, '*' },
    { 43, '+' },
    { 44, ',' },
    { 45, '-' },
    { 46, '.' },
    { 47, '/' },
    { 48, '0' },
    { 49, '1' },
    { 50, '2' },
    { 51, '3' },
    { 52, '4' },
    { 53, '5' },
    { 54, '6' },
    { 55, '7' },
    { 56, '8' },
    { 57, '9' },
    { 58, ':' },
    { 59, ';' },
    { 60, '<' },
    { 61, '=' },
    { 62, '>' },
    { 63, '?' },
    { 64, 0x2500 }, /* ─ horizontal box drawing line */
    { 65, 0x2660 }, /* ♠ black spade suit */
    { 66, 0x2502 }, /* │ vertical 1/8 block 4 */
    { 67, 0x1fb79 }, /* 🭹 horizontal 1/8 block 5 */
    { 68, 0x1fb78 }, /* 🭸 horizontal 1/8 block 4 */
    { 69, 0x1fb77 }, /* 🭷 horizontal 1/8 block 3 */
    { 70, 0x1fb7a }, /* 🭶 horizontal 1/8 block 6 */
    { 71, 0x1fb71 }, /* 🭱 vertical 1/8 block 3 */
    { 72, 0x1fb73 }, /* 🭳 vertical 1/8 block 5 */
    { 73, 0x256e }, /* ╮ left-bottom arc connector */
    { 74, 0x2570 }, /* ╰ right-top arc connector */
    { 75, 0x256f }, /* ╯ left-top arc connector */
    { 76, 0x1fb7c }, /* 🭼 left and lower one-eight corner */
    { 77, 0x2572 }, /* ╲ box drawing light diagonal UL to LR */
    { 78, 0x2571 }, /* ╱ box drawing light diagonal UR to LL */
    { 79, 0x1fb7d }, /* 🭽 left and upper one-eight corner */
    { 80, 0x1fb7e }, /* 🭾 right and upper one-eight corner */
    { 81, 0x25cf }, /* ● black circle */
    { 82, 0x1fb7b }, /* 🭻 horizontal 1/8 block 7 */
    { 83, 0x2665 }, /* ♥ black heart suit */
    { 84, 0x1fb70 }, /* 🭰 vertical 1/8 block 2 */
    { 85, 0x256d }, /* ╭ right-bottom arc connector */
    { 86, 0x2573 }, /* ╳ box drawing light cross */
    { 87, 0x25cb }, /* ○ white circle */
    { 88, 0x2663 }, /* ♣ black club suit */
    { 89, 0x1fb75 }, /* 🭵 vertical 1/8 block 7 */
    { 90, 0x2666 }, /* ♦ black diamond suit */
    { 91, 0x253c }, /* ┼ box drawing light vertical and horizontal */
    { 92, 0x1fb8c }, /* 🮌 left half medium shade (kinda) */
    { 93, 0x2502 }, /* │ vertical box drawing line */
    { 94, 0x03c0 }, /* π greek small letter Pi */
    { 95, 0x25e5 }, /* ◥ black upper right triangle */
    { 96, ' ' }, /* looks like a space (identical to #32) */
    { 97, 0x258c }, /* ▌ left half block */
    { 98, 0x2584 }, /* ▄ lower half block */
    { 99, 0x23ba }, /* ⎺ horizontal scan line 1 (upper) */
    { 100, 0x23bd }, /* ⎽ horizontal scan line 9 (lower) */
    { 101, 0x258f }, /* ▏ left 1/8 block */
    { 102, 0x1fb95 }, /* 🮕 checker board fill */
    { 103, 0x2595 }, /* ▕ right 1/8 block */
    { 104, 0x1fb8f }, /* 🮏 lower half medium shade (kinda) */
    { 105, 0x25e4 }, /* ◤ black upper left triangle */
    { 106, 0x2595 }, /* ▕ right 1/8 block (identical to #103) */
    { 107, 0x251c }, /* ├ box drawing light vertical and right */
    { 108, 0x2597 }, /* ▗ quadrant lower right */
    { 109, 0x2514 }, /* └ box drawing light up and right */
    { 110, 0x2510 }, /* ┐ box drawing light down and left */
    { 111, 0x2581 }, /* ▁ lower 1/8 block */
    { 112, 0x250c }, /* ┌ box drawing light down and right */
    { 113, 0x2534 }, /* ┴ box drawing light up and horizontal */
    { 114, 0x252c }, /* ┬ box drawing light down and horizontal */
    { 115, 0x2524 }, /* ┤ box drawing light vertical and left */
    { 116, 0x258f }, /* ▏ left 1/8 block (identical to #101) */
    { 117, 0x258e }, /* ▎ left 1/4 block */
    { 118, 0x1fb87 }, /* 🮇 right 1/4 block */
    { 119, 0x2594 }, /* ▔ upper 1/8 block */
    { 120, 0x1fb82 }, /* 🮂 upper 1/4 block */
    { 121, 0x2582 }, /* ▂ lower 1/4 block */
    { 122, 0x1fb7f }, /* 🭿 right and lower 1/8 corner */
    { 123, 0x2596 }, /* ▖ quadrant lower left */
    { 124, 0x259d }, /* ▝ quadrant upper right */
    { 125, 0x2518 }, /* ┘ box drawing light up and left */
    { 126, 0x2598 }, /* ▘ quadrant upper left */
    { 127, 0x259a }, /* ▚ quadrant upper left and lower right */

    /* Chars 128-255 are inverted versions of 0-127. Some of them make sense
     * as plain characters too. We list those here. */

    { 160, 0x2588 }, /* █ full block */
    { 214, 0x1fbbd }, /* 🮽 negative diagonal cross */
    { 220, 0x1fb94 }, /* 🮔 left medium half inverse medium shade and right half block (kinda) */
    { 223, 0x25e3 }, /* ◣ black lower left triangle */
    { 225, 0x2590 }, /* ▐ right half block */
    { 226, 0x2580 }, /* ▀ upper half block */
    { 229, 0x1fb8b }, /* 🮋 right 7/8 block */
    { 230, 0x1fb96 }, /* 🮖 inverse checker board fill */
    { 231, 0x2589 }, /* ▉ left 7/8 block */
    { 232, 0x1fb91 }, /* 🮑 upper half block and lower half inverse medium shade (kinda) */
    { 233, 0x25e2 }, /* ◢ black lower right triangle */
    { 234, 0x2589 }, /* ▉ left 7/8 block, (identical to #231) */
    { 236, 0x259b }, /* ▛ quadrant UL and UR and LL */
    { 239, 0x1fb86 }, /* 🮆 upper 7/8 block */
    { 244, 0x1fb8b }, /* 🮋 right 7/8 block (identical to #229) */
    { 245, 0x1fb8a }, /* 🮊 right 3/4 block */
    { 246, 0x258a }, /* ▊ left 3/4 block */
    { 247, 0x2587 }, /* ▇ lower 7/8 block */
    { 248, 0x2586 }, /* ▆ lower 3/4 block */
    { 249, 0x1fb85 }, /* 🮅 upper 3/4 block */
    { 251, 0x259c }, /* ▜ quadrant UL and UR and LR */
    { 252, 0x2599 }, /* ▙ quadrant UL and LL and LR */
    { 254, 0x259f }, /* ▟ quadrant UR and LL and LR */
    { 255, 0x259e }, /* ▞ quadrant upper right and lower left */
    { -1, 0 }
};

static const CodeMap ibm_codes [] =
{
    { 32, 0x0020 }, /* SPACE */
    { 33, 0x0021 }, /* EXCLAMATION MARK */
    { 34, 0x0022 }, /* QUOTATION MARK */
    { 35, 0x0023 }, /* NUMBER SIGN */
    { 36, 0x0024 }, /* DOLLAR SIGN */
    { 37, 0x0025 }, /* PERCENT SIGN */
    { 38, 0x0026 }, /* AMPERSAND */
    { 39, 0x0027 }, /* APOSTROPHE */
    { 40, 0x0028 }, /* LEFT PARENTHESIS */
    { 41, 0x0029 }, /* RIGHT PARENTHESIS */
    { 42, 0x002a }, /* ASTERISK */
    { 43, 0x002b }, /* PLUS SIGN */
    { 44, 0x002c }, /* COMMA */
    { 45, 0x002d }, /* HYPHEN-MINUS */
    { 46, 0x002e }, /* FULL STOP */
    { 47, 0x002f }, /* SOLIDUS */
    { 48, 0x0030 }, /* DIGIT ZERO */
    { 49, 0x0031 }, /* DIGIT ONE */
    { 50, 0x0032 }, /* DIGIT TWO */
    { 51, 0x0033 }, /* DIGIT THREE */
    { 52, 0x0034 }, /* DIGIT FOUR */
    { 53, 0x0035 }, /* DIGIT FIVE */
    { 54, 0x0036 }, /* DIGIT SIX */
    { 55, 0x0037 }, /* DIGIT SEVEN */
    { 56, 0x0038 }, /* DIGIT EIGHT */
    { 57, 0x0039 }, /* DIGIT NINE */
    { 58, 0x003a }, /* COLON */
    { 59, 0x003b }, /* SEMICOLON */
    { 60, 0x003c }, /* LESS-THAN SIGN */
    { 61, 0x003d }, /* EQUALS SIGN */
    { 62, 0x003e }, /* GREATER-THAN SIGN */
    { 63, 0x003f }, /* QUESTION MARK */
    { 64, 0x0040 }, /* COMMERCIAL AT */
    { 65, 0x0041 }, /* LATIN CAPITAL LETTER A */
    { 66, 0x0042 }, /* LATIN CAPITAL LETTER B */
    { 67, 0x0043 }, /* LATIN CAPITAL LETTER C */
    { 68, 0x0044 }, /* LATIN CAPITAL LETTER D */
    { 69, 0x0045 }, /* LATIN CAPITAL LETTER E */
    { 70, 0x0046 }, /* LATIN CAPITAL LETTER F */
    { 71, 0x0047 }, /* LATIN CAPITAL LETTER G */
    { 72, 0x0048 }, /* LATIN CAPITAL LETTER H */
    { 73, 0x0049 }, /* LATIN CAPITAL LETTER I */
    { 74, 0x004a }, /* LATIN CAPITAL LETTER J */
    { 75, 0x004b }, /* LATIN CAPITAL LETTER K */
    { 76, 0x004c }, /* LATIN CAPITAL LETTER L */
    { 77, 0x004d }, /* LATIN CAPITAL LETTER M */
    { 78, 0x004e }, /* LATIN CAPITAL LETTER N */
    { 79, 0x004f }, /* LATIN CAPITAL LETTER O */
    { 80, 0x0050 }, /* LATIN CAPITAL LETTER P */
    { 81, 0x0051 }, /* LATIN CAPITAL LETTER Q */
    { 82, 0x0052 }, /* LATIN CAPITAL LETTER R */
    { 83, 0x0053 }, /* LATIN CAPITAL LETTER S */
    { 84, 0x0054 }, /* LATIN CAPITAL LETTER T */
    { 85, 0x0055 }, /* LATIN CAPITAL LETTER U */
    { 86, 0x0056 }, /* LATIN CAPITAL LETTER V */
    { 87, 0x0057 }, /* LATIN CAPITAL LETTER W */
    { 88, 0x0058 }, /* LATIN CAPITAL LETTER X */
    { 89, 0x0059 }, /* LATIN CAPITAL LETTER Y */
    { 90, 0x005a }, /* LATIN CAPITAL LETTER Z */
    { 91, 0x005b }, /* LEFT SQUARE BRACKET */
    { 92, 0x005c }, /* REVERSE SOLIDUS */
    { 93, 0x005d }, /* RIGHT SQUARE BRACKET */
    { 94, 0x005e }, /* CIRCUMFLEX ACCENT */
    { 95, 0x005f }, /* LOW LINE */
    { 96, 0x0060 }, /* GRAVE ACCENT */
    { 97, 0x0061 }, /* LATIN SMALL LETTER A */
    { 98, 0x0062 }, /* LATIN SMALL LETTER B */
    { 99, 0x0063 }, /* LATIN SMALL LETTER C */
    { 100, 0x0064 }, /* LATIN SMALL LETTER D */
    { 101, 0x0065 }, /* LATIN SMALL LETTER E */
    { 102, 0x0066 }, /* LATIN SMALL LETTER F */
    { 103, 0x0067 }, /* LATIN SMALL LETTER G */
    { 104, 0x0068 }, /* LATIN SMALL LETTER H */
    { 105, 0x0069 }, /* LATIN SMALL LETTER I */
    { 106, 0x006a }, /* LATIN SMALL LETTER J */
    { 107, 0x006b }, /* LATIN SMALL LETTER K */
    { 108, 0x006c }, /* LATIN SMALL LETTER L */
    { 109, 0x006d }, /* LATIN SMALL LETTER M */
    { 110, 0x006e }, /* LATIN SMALL LETTER N */
    { 111, 0x006f }, /* LATIN SMALL LETTER O */
    { 112, 0x0070 }, /* LATIN SMALL LETTER P */
    { 113, 0x0071 }, /* LATIN SMALL LETTER Q */
    { 114, 0x0072 }, /* LATIN SMALL LETTER R */
    { 115, 0x0073 }, /* LATIN SMALL LETTER S */
    { 116, 0x0074 }, /* LATIN SMALL LETTER T */
    { 117, 0x0075 }, /* LATIN SMALL LETTER U */
    { 118, 0x0076 }, /* LATIN SMALL LETTER V */
    { 119, 0x0077 }, /* LATIN SMALL LETTER W */
    { 120, 0x0078 }, /* LATIN SMALL LETTER X */
    { 121, 0x0079 }, /* LATIN SMALL LETTER Y */
    { 122, 0x007a }, /* LATIN SMALL LETTER Z */
    { 123, 0x007b }, /* LEFT CURLY BRACKET */
    { 124, 0x007c }, /* VERTICAL LINE */
    { 125, 0x007d }, /* RIGHT CURLY BRACKET */
    { 126, 0x007e }, /* TILDE */
    { 128, 0x00c7 }, /* LATIN CAPITAL LETTER C WITH CEDILLA */
    { 129, 0x00fc }, /* LATIN SMALL LETTER U WITH DIAERESIS */
    { 130, 0x00e9 }, /* LATIN SMALL LETTER E WITH ACUTE */
    { 131, 0x00e2 }, /* LATIN SMALL LETTER A WITH CIRCUMFLEX */
    { 132, 0x00e4 }, /* LATIN SMALL LETTER A WITH DIAERESIS */
    { 133, 0x00e0 }, /* LATIN SMALL LETTER A WITH GRAVE */
    { 134, 0x00e5 }, /* LATIN SMALL LETTER A WITH RING ABOVE */
    { 135, 0x00e7 }, /* LATIN SMALL LETTER C WITH CEDILLA */
    { 136, 0x00ea }, /* LATIN SMALL LETTER E WITH CIRCUMFLEX */
    { 137, 0x00eb }, /* LATIN SMALL LETTER E WITH DIAERESIS */
    { 138, 0x00e8 }, /* LATIN SMALL LETTER E WITH GRAVE */
    { 139, 0x00ef }, /* LATIN SMALL LETTER I WITH DIAERESIS */
    { 140, 0x00ee }, /* LATIN SMALL LETTER I WITH CIRCUMFLEX */
    { 141, 0x00ec }, /* LATIN SMALL LETTER I WITH GRAVE */
    { 142, 0x00c4 }, /* LATIN CAPITAL LETTER A WITH DIAERESIS */
    { 143, 0x00c5 }, /* LATIN CAPITAL LETTER A WITH RING ABOVE */
    { 144, 0x00c9 }, /* LATIN CAPITAL LETTER E WITH ACUTE */
    { 145, 0x00e6 }, /* LATIN SMALL LIGATURE AE */
    { 146, 0x00c6 }, /* LATIN CAPITAL LIGATURE AE */
    { 147, 0x00f4 }, /* LATIN SMALL LETTER O WITH CIRCUMFLEX */
    { 148, 0x00f6 }, /* LATIN SMALL LETTER O WITH DIAERESIS */
    { 149, 0x00f2 }, /* LATIN SMALL LETTER O WITH GRAVE */
    { 150, 0x00fb }, /* LATIN SMALL LETTER U WITH CIRCUMFLEX */
    { 151, 0x00f9 }, /* LATIN SMALL LETTER U WITH GRAVE */
    { 152, 0x00ff }, /* LATIN SMALL LETTER Y WITH DIAERESIS */
    { 153, 0x00d6 }, /* LATIN CAPITAL LETTER O WITH DIAERESIS */
    { 154, 0x00dc }, /* LATIN CAPITAL LETTER U WITH DIAERESIS */
    { 155, 0x00a2 }, /* CENT SIGN */
    { 156, 0x00a3 }, /* POUND SIGN */
    { 157, 0x00a5 }, /* YEN SIGN */
    { 158, 0x20a7 }, /* PESETA SIGN */
    { 159, 0x0192 }, /* LATIN SMALL LETTER F WITH HOOK */
    { 160, 0x00e1 }, /* LATIN SMALL LETTER A WITH ACUTE */
    { 161, 0x00ed }, /* LATIN SMALL LETTER I WITH ACUTE */
    { 162, 0x00f3 }, /* LATIN SMALL LETTER O WITH ACUTE */
    { 163, 0x00fa }, /* LATIN SMALL LETTER U WITH ACUTE */
    { 164, 0x00f1 }, /* LATIN SMALL LETTER N WITH TILDE */
    { 165, 0x00d1 }, /* LATIN CAPITAL LETTER N WITH TILDE */
    { 166, 0x00aa }, /* FEMININE ORDINAL INDICATOR */
    { 167, 0x00ba }, /* MASCULINE ORDINAL INDICATOR */
    { 168, 0x00bf }, /* INVERTED QUESTION MARK */
    { 169, 0x2310 }, /* REVERSED NOT SIGN */
    { 170, 0x00ac }, /* NOT SIGN */
    { 171, 0x00bd }, /* VULGAR FRACTION ONE HALF */
    { 172, 0x00bc }, /* VULGAR FRACTION ONE QUARTER */
    { 173, 0x00a1 }, /* INVERTED EXCLAMATION MARK */
    { 174, 0x00ab }, /* LEFT-POINTING DOUBLE ANGLE QUOTATION MARK */
    { 175, 0x00bb }, /* RIGHT-POINTING DOUBLE ANGLE QUOTATION MARK */
    { 176, 0x2591 }, /* LIGHT SHADE */
    { 177, 0x2592 }, /* MEDIUM SHADE */
    { 178, 0x2593 }, /* DARK SHADE */
    { 179, 0x2502 }, /* BOX DRAWINGS LIGHT VERTICAL */
    { 180, 0x2524 }, /* BOX DRAWINGS LIGHT VERTICAL AND LEFT */
    { 181, 0x2561 }, /* BOX DRAWINGS VERTICAL SINGLE AND LEFT DOUBLE */
    { 182, 0x2562 }, /* BOX DRAWINGS VERTICAL DOUBLE AND LEFT SINGLE */
    { 183, 0x2556 }, /* BOX DRAWINGS DOWN DOUBLE AND LEFT SINGLE */
    { 184, 0x2555 }, /* BOX DRAWINGS DOWN SINGLE AND LEFT DOUBLE */
    { 185, 0x2563 }, /* BOX DRAWINGS DOUBLE VERTICAL AND LEFT */
    { 186, 0x2551 }, /* BOX DRAWINGS DOUBLE VERTICAL */
    { 187, 0x2557 }, /* BOX DRAWINGS DOUBLE DOWN AND LEFT */
    { 188, 0x255d }, /* BOX DRAWINGS DOUBLE UP AND LEFT */
    { 189, 0x255c }, /* BOX DRAWINGS UP DOUBLE AND LEFT SINGLE */
    { 190, 0x255b }, /* BOX DRAWINGS UP SINGLE AND LEFT DOUBLE */
    { 191, 0x2510 }, /* BOX DRAWINGS LIGHT DOWN AND LEFT */
    { 192, 0x2514 }, /* BOX DRAWINGS LIGHT UP AND RIGHT */
    { 193, 0x2534 }, /* BOX DRAWINGS LIGHT UP AND HORIZONTAL */
    { 194, 0x252c }, /* BOX DRAWINGS LIGHT DOWN AND HORIZONTAL */
    { 195, 0x251c }, /* BOX DRAWINGS LIGHT VERTICAL AND RIGHT */
    { 196, 0x2500 }, /* BOX DRAWINGS LIGHT HORIZONTAL */
    { 197, 0x253c }, /* BOX DRAWINGS LIGHT VERTICAL AND HORIZONTAL */
    { 198, 0x255e }, /* BOX DRAWINGS VERTICAL SINGLE AND RIGHT DOUBLE */
    { 199, 0x255f }, /* BOX DRAWINGS VERTICAL DOUBLE AND RIGHT SINGLE */
    { 200, 0x255a }, /* BOX DRAWINGS DOUBLE UP AND RIGHT */
    { 201, 0x2554 }, /* BOX DRAWINGS DOUBLE DOWN AND RIGHT */
    { 202, 0x2569 }, /* BOX DRAWINGS DOUBLE UP AND HORIZONTAL */
    { 203, 0x2566 }, /* BOX DRAWINGS DOUBLE DOWN AND HORIZONTAL */
    { 204, 0x2560 }, /* BOX DRAWINGS DOUBLE VERTICAL AND RIGHT */
    { 205, 0x2550 }, /* BOX DRAWINGS DOUBLE HORIZONTAL */
    { 206, 0x256c }, /* BOX DRAWINGS DOUBLE VERTICAL AND HORIZONTAL */
    { 207, 0x2567 }, /* BOX DRAWINGS UP SINGLE AND HORIZONTAL DOUBLE */
    { 208, 0x2568 }, /* BOX DRAWINGS UP DOUBLE AND HORIZONTAL SINGLE */
    { 209, 0x2564 }, /* BOX DRAWINGS DOWN SINGLE AND HORIZONTAL DOUBLE */
    { 210, 0x2565 }, /* BOX DRAWINGS DOWN DOUBLE AND HORIZONTAL SINGLE */
    { 211, 0x2559 }, /* BOX DRAWINGS UP DOUBLE AND RIGHT SINGLE */
    { 212, 0x2558 }, /* BOX DRAWINGS UP SINGLE AND RIGHT DOUBLE */
    { 213, 0x2552 }, /* BOX DRAWINGS DOWN SINGLE AND RIGHT DOUBLE */
    { 214, 0x2553 }, /* BOX DRAWINGS DOWN DOUBLE AND RIGHT SINGLE */
    { 215, 0x256b }, /* BOX DRAWINGS VERTICAL DOUBLE AND HORIZONTAL SINGLE */
    { 216, 0x256a }, /* BOX DRAWINGS VERTICAL SINGLE AND HORIZONTAL DOUBLE */
    { 217, 0x2518 }, /* BOX DRAWINGS LIGHT UP AND LEFT */
    { 218, 0x250c }, /* BOX DRAWINGS LIGHT DOWN AND RIGHT */
    { 219, 0x2588 }, /* FULL BLOCK */
    { 220, 0x2584 }, /* LOWER HALF BLOCK */
    { 221, 0x258c }, /* LEFT HALF BLOCK */
    { 222, 0x2590 }, /* RIGHT HALF BLOCK */
    { 223, 0x2580 }, /* UPPER HALF BLOCK */
    { 224, 0x03b1 }, /* GREEK SMALL LETTER ALPHA */
    { 225, 0x00df }, /* LATIN SMALL LETTER SHARP S */
    { 226, 0x0393 }, /* GREEK CAPITAL LETTER GAMMA */
    { 227, 0x03c0 }, /* GREEK SMALL LETTER PI */
    { 228, 0x03a3 }, /* GREEK CAPITAL LETTER SIGMA */
    { 229, 0x03c3 }, /* GREEK SMALL LETTER SIGMA */
    { 230, 0x00b5 }, /* MICRO SIGN */
    { 231, 0x03c4 }, /* GREEK SMALL LETTER TAU */
    { 232, 0x03a6 }, /* GREEK CAPITAL LETTER PHI */
    { 233, 0x0398 }, /* GREEK CAPITAL LETTER THETA */
    { 234, 0x03a9 }, /* GREEK CAPITAL LETTER OMEGA */
    { 235, 0x03b4 }, /* GREEK SMALL LETTER DELTA */
    { 236, 0x221e }, /* INFINITY */
    { 237, 0x03c6 }, /* GREEK SMALL LETTER PHI */
    { 238, 0x03b5 }, /* GREEK SMALL LETTER EPSILON */
    { 239, 0x2229 }, /* INTERSECTION */
    { 240, 0x2261 }, /* IDENTICAL TO */
    { 241, 0x00b1 }, /* PLUS-MINUS SIGN */
    { 242, 0x2265 }, /* GREATER-THAN OR EQUAL TO */
    { 243, 0x2264 }, /* LESS-THAN OR EQUAL TO */
    { 244, 0x2320 }, /* TOP HALF INTEGRAL */
    { 245, 0x2321 }, /* BOTTOM HALF INTEGRAL */
    { 246, 0x00f7 }, /* DIVISION SIGN */
    { 247, 0x2248 }, /* ALMOST EQUAL TO */
    { 248, 0x00b0 }, /* DEGREE SIGN */
    { 249, 0x2219 }, /* BULLET OPERATOR */
    { 250, 0x00b7 }, /* MIDDLE DOT */
    { 251, 0x221a }, /* SQUARE ROOT */
    { 252, 0x207f }, /* SUPERSCRIPT LATIN SMALL LETTER N */
    { 253, 0x00b2 }, /* SUPERSCRIPT TWO */
    { 254, 0x25a0 }, /* BLACK SQUARE */

    { -1, 0 }
};