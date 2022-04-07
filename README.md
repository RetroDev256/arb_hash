# arb_hash
Arbitrary block length hash function, potentially cryptographically secure. Passes BigCrush

Usage:
- Create two AHBlock structures, for the input to the hash function, and the output from the hash function
- The data field should consist of a pointer to N bytes of memory, with the count field set to N
- The output structure must have at least the same value for N
- The input and output must point to seperate, non overlapping places in memory
- The value for N in both the input and output structures must be at least 3

