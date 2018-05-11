# Questions

## What is pneumonoultramicroscopicsilicovolcanoconiosis?

**A**: An invented long word said to mean a lung disease caused by inhaling very fine ash and sand dust.

## According to its man page, what does `getrusage` do?

**A**: `getrusage` returns resource usage measures for one of the following: a) the calling process (sum of resources used by all its threads), b) all children
        of the calling process (that have been terminated and been waited for), or, for c) the calling thread.

## Per that same man page, how many members are in a variable of type `struct rusage`?

**A**: There are 16 variables in a variable of type `struct rusage` (6 of these fields are currently unused by Linux).

## Why do you think we pass `before` and `after` by reference (instead of by value) to `calculate`, even though we're not changing their contents?

**A**: This is because the `calculate` function expects as its arguments pointers to variables of type `struct rusage`.

## Explain as precisely as possible, in a paragraph or more, how `main` goes about reading words from a file. In other words, convince us that you indeed understand how that function's `for` loop works.

**A**: `main` begins by reading the input text file character by character, checking to see if the character that has just been read is an alphabet or an apostraphe ('),
        and appends it to a character array called `word`. We keep track of the size of this character array using a variable calles `index`, which is updated after each
        character is added to the array. If the index exceeds the maximum length of the `word` array (45 in this case), we use a for loop to run through the rest of the
        characters in the word being read from the text file until we arrive at the next word - this is akin to fast-forwarding or advancing the 'read' location in
        the input file. We reset the `index` to 0 at the end of such a word, so we can start counting the characters of a new word.
        We do a similar thing of running through characters of words (which is a way of not considering these words) which are alphanumeric. For all other words that have
        a length greater than 0 and less than `index`, and ones that don't have any numbers in them, we add a trailing '\0' character to mark the end of a whole 'legal'
        (in this case) word.
        We then call the `check` function one each word to decide if the word is misspelled (i.e., it does not exist in the specified dictionary) - in which case, we
        print that word and update the misspellings counter, which keeps track of how many misspelled words there are in the input file.

## Why do you think we used `fgetc` to read each word's characters one at a time rather than use `fscanf` with a format string like `"%s"` to read whole words at a time? Put another way, what problems might arise by relying on `fscanf` alone?

**A**: Using `fgetc` has a couple of advantages over using `fscanf`:
        a) `fgetc` lets us read the input file character by character - this lets us keep track of the number of characters we have read; this is helpful in cases
            where the file might contain words longer than what we wish to read - which can lead to segmentation faults.
        b) When reading from a file, it is often the case that words end with special characters (comma, period, etc.). `fscanf` will interpret these characters as being part
            of the words they are attached to, which can be problematic during word comparisons. `fscanf` could be chosen over `fgetc` in cases where the input file is formatted
            such that all the words/strings (without special characters at the end) have a trailing '\n' and/or '\0' character.

## Why do you think we declared the parameters for `check` and `load` as `const` (which means "constant")?

**A**: This is to indicate to the C compiler that `word` and `dictionary` are pointers to constant characters, i.e., the functions using them will not change the value of
        the variables they are pointing to _through the pointers_. In other words, statements of the kind: *word = 'Hello' or *dictionary = 'AnotherDictionary' are invalid.
