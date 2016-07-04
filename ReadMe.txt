========================================================================
     ShakespeareMonkeys Project Overview
========================================================================

This is an example of a simple genetic algorithm. The task is to find
shakespeare's famous line "to be or not to be" using an aggressive form of
selective breeding. This is why it is called Shakespeare monkeys, the old 
question concerned how long it would take a population of monkeys to think of
the line. 

The Chromosome of the monkeys is more like the Chromosome of a block of text.
If you imagine that each character of the text is a gene and the monkey with 
certain DNA will produce the famous quote, then you are on the right track.

At the beginning a population of monkeys (chromosomes) is created. The population
size can be varied. Each monkey starts with a random set of letter's for the 
chromosome. The monkeys chromosome is compared to the target chromosome 
"to be or not to be" and then the monkey is given a fitness score. This score
is then used to select monkeys for breeding, the monkeys with the highest fitness 
(percentage simmilarity to the target) have a better chance of selection, imagine
they have a proportionally better slice of a pie and a roulette wheel is then used
to select the monkey whose slice the arrow lands in. The breeding operation is simply 
a mixture of genes from the two paired breeding monkeys. After the breeding there is a
chance for mutation that selects a random gene and finds another random letter for the
gene.

The process then repeats until a monkey says the line from the target.


