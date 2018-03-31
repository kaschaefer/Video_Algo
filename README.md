Notes From the Problem Solver:

By the time I finished coding a solution that I was okay with submitting, I realized that a lookup table would have been immensely helpful in this scenario. There are definitely better solutions out there, performance wise, but this was the one I felt like I could wrap my mind around and implement in (close to) the time given. 






# Problem

Suppose we have 2 videos of the same event, shot with different cameras. For example, somebody shot footage driving a
car with 2 cameras: one facing into the car and one facing out.

Our machine learning algorithms have identified a set of "moments" from each camera. A moment is just a section of a
video. Given these two lists of we want to select a total of `k` moments to create an edited video. For example, the
input might be:

```
Camera 1: [c1m1, c1m2]
Camera 2: [c2m1, c2m2, c2m3]
k: 3
```

Those inputs indicate that we want to select 3 total moments (because `k` is 3) for our final video. Our algorithms
identified 2 moments from the video shot by camera 1 (c1m1, and c1m2) and 3 moments from the video shot by camera 2
(c2m1, c2m2, and c2m3). What we want as output is all the length `k` permutations (`k == 3` in this example) of those
moments so we can decide which makes the best video (assume some other function will assess the list of moments for
quality). However, there is one other constraint: We always want adjacent clips to switch camera views. That is, if the
first section of our final video is from the camera facing into the car the next clip should come from the camera facing
out of the car, and the one after that should switch back to the inward facing camera, etc. So, given the example inputs
above the correct output should contain:

```
[c1m1, c2m1, c1m2]
[c1m1, c2m2, c1m2]
[c1m1, c2m3, c1m2]
[c1m2, c2m1, c1m1]
[c1m2, c2m2, c1m1]
[c1m2, c2m3, c1m1]
[c2m1, c1m1, c2m2]
[c2m1, c1m2, c2m2]
[c2m1, c1m1, c2m3]
[c2m1, c1m2, c2m3]
[c2m2, c1m1, c2m1]
[c2m2, c1m2, c2m1]
[c2m2, c1m1, c2m3]
[c2m2, c1m2, c2m3]
[c2m3, c1m1, c2m1]
[c2m3, c1m2, c2m1]
[c2m3, c1m1, c2m2]
[c2m3, c1m2, c2m2]
```

The order of the output doesn't matter. All that matters is that it contains all legal permutations. Note that in every
permutation above we alternate between camera 1 and camera 2.

To solve this challenge you must write a C++ function with the following signature:

```
unique_ptr<vector<vector<Moment>> AllPossibleEdits(
    const vector<Moment>& camera_one_moments,
    const vector<Moment>& camera_two_moments,
    int k);
```

Where `unique_ptr`, and `vector` come from the C++ standard library (so they're in namespace `std`) and the
`Moment` class is just a simple class that indicates which video it came from and what parts of the video to keep. The
output is a smart pointer to a `vector` of `vector` of `Moment` where the inner `vector<Moment>` is one possible
permutation of moments.

The code you will work on is in `code.h` and `code.cpp`. In particular, you will need to implement the above method in
`code.cpp`.

# Tests

The project contains some unit tests in `test.cpp`. Obviously, initially those tests won't pass. Your task is to make
them all pass. Feel free to add additional tests if you want.

The unit tests use [Catch2](https://github.com/catchorg/Catch2). The Catch2 code is in the `catch.h` file. There
shouldn't be any reason you need to look at the code in there.

# Building

We are using [CMake](https://cmake.org/) to build this code. Cmake is a "meta build tool"; it doesn't actually build
your code. Instead it generates configuration files for other build systems. It can generate traditional make files, but
it can also generate project files for many popular IDEs. If you use one of those IDEs you might want to use that
functionality. The [CMake documention](https://cmake.org/cmake/help/v3.11/manual/cmake-generators.7.html) contains a
list of the supported IDEs.

If you just want to build from the command line the following should work:

1. Create a directory for the build: `mkdir build`
2. Change to that directory: `cd build`
3. Run CMake to generate a `Makefile`: `cmake ..`
4. You can now build your code by running `make`

You will not have to repeat steps 1 - 3. After editing your code you can rebuild by just running `make`.

The build will generate an executable in the `build` directory called `tests` (on Windows it may get a `.exe`
extension). You can run that executable to run your tests. The output should look something like:

```
$ ./build/tests
===============================================================================
All tests passed (576 assertions in 3 test cases)
```

If CMake is not your preferred build tool feel free to use something else.

# Criteria

When we look at your submission we will look for:

* Correctness: does it actually solve the problem?
* Code quality: is your code maintainable, readable, well commented, broken up into reasonable sized pieces, etc.?
* Performance: Is your solution reasonably efficient?

# Submission

When you have completed the challenge push it to a public git repository somewhere and email us a link to the repo.
