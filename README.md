# Welcome to JenSeq

This is a very small program to showcase sequence alignment using the [Needleman-Wunsch algorithm](https://en.wikipedia.org/wiki/Needleman%E2%80%93Wunsch_algorithm). 

To run it, currently, the generated .exe doesn't work and I haven't had time to discover why.
You will need to download [QT Creator Community (version 20.0.1)](https://www.qt.io/development/download-qt-installer-oss) and then use the CMakeLists.txt to open and compile the project.

Then you can run it, there are 2 examples in the dropdown that you can use to observe the sequence alignent.

A note: this program shows one possible alignment. In reality, this algorithm can usually give multiple options for alignments that would then be individually scored to find "the best" one. Sometimes two options for alignment will score the same and then you just have 2 possible alignments. 

Alternative alignments come from a point on the matrix getting the same highest score from more than one direction.

For future development - I would like a way to show all possible alignments. But right now, it only shows one. 

If you're just here to look at the code - I'm so sorry. It's so ugly. I was on a time crunch of my own making. I have no excuse. Maybe I will clean it up in the future. Right now chances seem slim.

If you're having any issues with running the code or you want to cyberbully me, my email is: jenna.dunford@gmail.com
