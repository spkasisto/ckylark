Ckylark
=======

Ckylark - CKY-based latent annotated rule ekstractor


About
-----

This software generates the phrase structure of given input
sentence using latent annotated probabilistic context-free
grammar (LAPCFG) model proposed by [Petrov et al., 2006]
[Petrov, 2009].

Since original LAPCFG Parser sometimes makes failed parses in
parse-time, our implementation avoids this problem using
below approaches:
* Using probabilities of unknown words for parse-time
  smoothing.
* Rollbacking coarse grammar if parsing failed.

"Ckylark" is a portmanteau of both "CKY" and "skylark."


Install
-------

You need `autotools` to build Ckylark.
You simply run below:

    cd /path/to/Ckylark
    autoreconf -i
    ./configure
    make


Usage
-----

For simply use, you can type below command to parse your
sentence:

    src/ckylark --model <model file> < <your corpus>

`--model` requires the prefix of model file like `model/wsj` in
this repository.
(if you need to parse Japanese, `model.jdc` instead)

You also can use your original models on Ckylark.
Ckylark can uses the text dump files of original Berkeley Parser models.

If you want to see all options, please type below:

    src/ckylark --help


Contributors
------------

* Yusuke Oda (@odashi) - Most coding
* Koichi Akabe (@vbkaisetsu)
* Graham Neubig (@neubig)

We are counting more contributions from you.


Contact
-------

If you find an issue, please contact Y.Oda
* yus.takara (at) gmail.com
* @odashi_t on Twitter

