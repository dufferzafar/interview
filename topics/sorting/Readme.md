
# Sorting

The ideal sorting algorithm would have the following properties:

* Stable: Equal keys aren't reordered.
* Operates in place, requiring O(1) extra space.
* Worst-case O(n lg(n)) key comparisons.
* Worst-case O(n) swaps.
* Adaptive: Speeds up to O(n) when data is nearly sorted or when there are few unique keys.

There is no algorithm that has all of these properties, and so the choice of sorting algorithm depends on the application:

| Criteria                                   | Sorting algorithm |
|:-------------------------------------------|------------------:|
| Only a few items                           |    Insertion Sort |
| Items are mostly sorted already            |    Insertion Sort |
| Concerned about worst-case scenarios       |         Heap Sort |
| Interested in a good average-case result   |        Quick Sort |
| Items are drawn from a dense universe      |       Bucket Sort |
| Desire to write as little code as possible |    Insertion Sort |

## Links

* https://www.toptal.com/developers/sorting-algorithms

    - Show how each algorithm operates.
    - Show that there is no best sorting algorithm.
    - Show the advantages and disadvantages of each algorithm.
    - Show that worse-case asymptotic behavior is not always the deciding factor in choosing an algorithm.
    - Show that the initial condition (input order and key distribution) affects performance as much as the algorithm choice.

* https://stackoverflow.com/questions/220044/which-sort-algorithm-works-best-on-mostly-sorted-data
