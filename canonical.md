Q. "So what is a canonical?"

A. Wikipedia defines the word as "Canonical is the adjective for canon, literally a 'rule', and has come to mean also 'standard', 'archetypal', 'typical', or 'unique distinguished exemplar'." A canonical, as used in computer science, is a standard format for the representation of information. It's really a necesary thing to agree on a canonical if you're going to share information.


Q. "You claim a canonical exponentially adds capability. How does that work?"

A. I think this can best be explained by example. Let's assume you want to convert any kind of image file to any other kind of file.

If there are three types of image files the usual response would be to create six programs: Two to convert from image type 1 (to the type 2 and 3), two to convert from type 2 (to type 1 and 3), and two to convert from type 3 (to type 1 and 2).

![https://xml-command-line.googlecode.com/git/images/CanonicalTutorial1.jpg](https://xml-command-line.googlecode.com/git/images/CanonicalTutorial1.jpg)

What if we do it a different way and establish a canonical image format? Instead of converting directly from type to type we create three programs to convert to the canonical format, and three to convert from the canonical to the each of the three types.

![https://xml-command-line.googlecode.com/git/images/CanonicalTutorial2.jpg](https://xml-command-line.googlecode.com/git/images/CanonicalTutorial2.jpg)

You might ask "how is this any better? It seems like the same amount of work either way."

That's true but consider what happens if a fourth image format is added.

Using a non canonical method you need to write six new programs: Convert 1 to 4, 2 to 4, 3 to 4, 4 to 1, 4 to 2, and 4 to 3.

Using a canonical method you need to write **two** new programs: Convert 4 to canonical, and canonical to 4. The amount of effort is **_1/3rd_** as large. As the number of image formats increases the benefit grows.

## Bonus! ##

Suppose you need to add the ability to edit images as well. If you create image editing programs that operate on the canonical format then you instantly gain the ability to edit any type of supported image.

I love getting free stuff. Canonicals are like Christmas without the great wrapping paper.

Better yet, if you understand [xslt](xslt.md) you can edit canonicals in very sophisticated ways with very small scripts.