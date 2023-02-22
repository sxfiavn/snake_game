# CSCI 0300 Project 1 - Snake

## Design Overview:

Snake game where a snake can be moved with the arrow buttons (up, down , left, right), eating food to increase score and grow (depending on the level).
Try not to touch the walls!
Good Luck :)

## Collaborators:

Sofia Vaca Narvaja Cordoba

## Responsible Computing:

Partner CS login: oweiss (Ottocaro Weiss)

1. Who founded the Consortium? Who is represented among the current members, and how might that affect decisions being made for Unicode?

   The founders of the Unicode Consortium were Joe Becker, Lee Collins and Mark Davis in 1991. Currently, the members of the Consortium represent: "major computer corporations, software producers, database vendors, government ministries, research institutions, international agencies, various user groups, and interested individuals." as they describe in their website (https://unicode.org/consortium/consort.html).

   At their start, it is pretty evident how the fact that their founding members were all white western english-speaking male software engineers could have biased what languages they included in Unicode's catalog and what cultural implications they understood. All in all, they represented a very limited portion and view of the world, as well as what people from other cultures could need to communicate.
   Currently, their Consortium seems to aim to tackle what I just criticised. Not only do they seem to include people from various cultural background and experiences, but also people coming from a range of different industries: software, corporations, government, research institutions, etc. With a wider range of perspectives and inputs from people in positions of constantly bringing things to the table in terms of what could be changed, Unicode has grown and matured to what it is today and it is still making changes. The addition of these perspectives and backgrounds can really be observed when looking at the trajectory of unicode: how much it has grown, how it has grown, how many languages and dialects have been added, etc.

2. Find a language that is not yet in Unicode, has only recently been supported (e.g., in the last 10 years), or is/was missing important characters. What is/was missing, and how does this affect the users of the language?

   Although the first time emojis where implemented in unicode was 2010, semi-recent close to 13 years ago, I find them interesting to talk about. As stated in Unicode's website Emojis: "which are treated as pictographs, are encoded in the Unicode Standard based primarily on their general appearance".
   The growth in popularity of Twitter and other similar platforms has made emojis a go-to way of expressing a wide range of emotions for people coming from all different backgrounds. And this wouldn't have been possible without their implementation in Unicode.
   Because of this, Emojis have more recently become a huge part of online culture and a must-have for anyone with a mobile device. They are used by everyone for texting friends and family, for CEOs and political figures to tweet about new updates and relate to younger generations, and more. In addition to that different cultures may give the same Emoji a different meaning, or even a single culture may give the same emoji a different meaning depending on the context.
   The use of these pictographs is an essential part of online and real-life culture. Emojis are the new pictures as they are worth a thousand words. For this, we also see how new emojis are implemented all the time and added to the unicode catalog, making it possible to stay in touch with what real humans want and need to communicate. A covid emoji, different skin toned emojis, etc.

   Source: https://unicode.org/faq/emoji_dingbats.html

3.

a) Outline either the position for Han Unification, or the position against Han Unification.

    The Chinese and Japanese languages cannot be used at the same time and its justified through the similarities between their characters.
    There are a lot of things that come with a language that get lost in common translation, imagine how much is lost if we try to have a single unicode for many languages mainly because they are different from traditional western writing.
    It sounds as if the unification was pushed more by western interests rather than those of the people who actually live their everyday lives using those languages.

    It also comes as a problem with more ancient Chinese writing and the difference with simplified Chinese (the one used today).

    I also wanted to note this that I found online which I found sums up the usability discussion quite nicely:
    "So the issue does come up when mixing Chinese and Japanese text, but it’s not really one that has a big impact on legibility of the text but you would definitely be concerned if you were writing a Japanese textbook for Chinese students, or vice versa."
    Source: https://news.ycombinator.com/item?id=22869632

    But the discussion should not only be about usability but also about its cultural implications.

    Still, I also understand Unicode is constantly working on fixing details.

b) Discussion:

    On accuracy:
    -> Sofi: The accuracy is lost on symbols that are similar but not exactly the same.
    -> Otto: These small issues are due to the implementation after-the-fact, not ASCII itself.

    On efficiencv:
    -> Otto: Fewer characters offers more efficiency on a variety of computations, including searching.
    -> Sofi: The efficiency gains are not super clear in each case, since Han Unification may require more post-character retrieval processing due to the subtle differences and exceptions.

    On fairness:
    -> Sofi: There are a lot of things that come with a language that get lost in common
    translation, imagine how much is lost if we try to have a single unicode for many languages just because they are different
    from traditional western writing. And, with China becoming its own global power, the Han Unification exerts its own form of centralizating influence.
    -> Otto: In terms of computing performance, non-alphabetical languages are at a disadvantage,
    and, in that case, Han Unification introduces more fairness with the Western alphebetic languages.

    On sustainabilty:
    -> Otto: As more characters get added to ASCII, it is important to reduce the number of characters already there, which allows for important additions as new symbols come into being.
    Sofi: The Han Unification may produce unwanted complications for programmers that will continue to exist for many years.

    It seems that the ASCII members chose to prioritize efficiency and sustainability above accuracy and fairness, which reflects the largely tech-minded membership, whose systems will benefit. On the other hand, many average users who do not have much
    interests in the small differences the change makes for efficiency and sustainability, making those whose languages may not be as precise the ultimate losers of the situation.

## Extra Credit attempted:

## How long did it take to complete Snake?

<!-- Enter an approximate number of hours that you spent actively working on the project. -->

17 hours (I was sick in the middle and had container issues so a lot of the time I spent on it wasn't particularly productive)
