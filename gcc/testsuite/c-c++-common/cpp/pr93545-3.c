/* PR preprocessor/93545 */
/* { dg-do preprocess } */

__has_include ("foobarbaz"	/* { dg-error "" } */
