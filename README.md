# hslocker
CLI tool for managing the keys for my HS class' lockers. Only works on Windows.

## Input format
It's similar to a CSV file, except the separator is `;`. File must be named `lockers.txt`. It reads values in the following format:
```
Student name;Has/doesn't have/never got key;Locker no.;Pair (if any)
```
###
Example: Susan has the key for locker 37 and shares it with kid no. 23 on the list
```
Susan;1;37;23
```
Example 2: Mary has no key
```
Mary;0;0;0
```
Example 3: Mark never got a key
```
Mark;2;0;0
```
