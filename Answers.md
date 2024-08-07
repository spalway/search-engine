# Assignment 4: Answers

**Complete this document, commit your changes to Github and submit the repository URL to Canvas.** Keep your answers short and precise.

Names of all team members:

Oyku Serap Ogut
Shan Palway

Used free extension: [ ] 24 hrs or [x] 48 hrs

[ ] Early submission (48 hrs)

[ ] Bonus work. Describe: ...

Place [x] for what applies.


## Answers

### Project Management

Complete the tasks and planned completion columns **BEFORE** You start with 
coding!


Weekly milestones/tasks. Set out a plan at the beginning and then record when you got it done.

| Task          | Planned completion | Actual completion | Time spent in hrs by Serap | Time spent in hrs by Shan     |
| -----------   | :-----------------:| :---------------: | :--------------------:     | :--------------------:        |
|AVL Tree Class | Nov 6              | Nov 10            | 4 hours                    | 2 hours                       |
|Document Parser| Nov 9              | Nov 12            | 3 hours                    | 1.5 hours                     |
|Query Class    | Nov 15             | Nov 17            | 5 hours                    | 1 hour                        | 
|Finish Testing | Nov 19             | Nov 21            | 2 hours                    | 2.5 hours                     |
|Search Engine  | Nov 25             | Nov 28            | 3 hours                    | 1.5 hours                     |
|Finalize       | Dec 3              | Dec 4             | 6 hours                    | 4 hours                       |


### High-level Design of Solution

- Add a UML class diagram, etc.
- High-level pseudo code for each component.

> Document Parser: 
class DocumentParser
    Method readJsonFile(path, wordTree, peopleMap, orgsMap, stopWordTree, docTree)
        Open the JSON file at path
        Parse the file into a document object
        Insert the document into docTree
        Extract and process entities (people, organizations) and words
        Insert processed data into wordTree, peopleMap, and orgsMap

    Method tokenize(tweet)
        Split the given tweet into words
        Return a list of words

    Method fileSystem(directoryPath, wordTree, peopleMap, orgsMap, stopWordTree, docTree)
        Iterate over all files in directoryPath
        For each file, call readJsonFile

    Method readStopWords(stopWordTree)
        Read and insert stop words into stopWordTree
        Return stopWordTree


>Index:
class Index
    Method makeWordPersist(wordTree, filepath)
        Write the wordTree to a file at filepath

    Method makeNamePersist(nameMap, filepath)
        Write the nameMap to a file at filepath

    Method makeDocTreePersist(docTree, filepath)
        Write the docTree to a file at filepath

    Method readWordPersist(tree, filepath)
        Read from a file at filepath and populate tree

    Method readNamePersist(tree, filepath)
        Read from a file at filepath and populate tree

    Method readDocTreePersist(docTree, filepath)
        Read from a file at filepath and populate docTree

>Query:
class Query
    Constructor Query()

    Method parseQuery(query, wordTree, people, orgs, stopWords)
        Process the query string and return a list of documents and their relevance

    Method parseAndProcessTerms(term, wordTree, finalMap)
        Process individual terms in the query

    Method parseAndProcessOrgs(org, orgs, finalMap)
        Process organization names in the query

    Method parseAndProcessPeople(person, people, finalMap)
        Process person names in the query

    Method excludeTerms(terms, finalMap)
        Exclude specific terms from the finalMap

    Method rankResults(finalMap)
        Rank the results based on relevance and return them

>UserInterface:
class UserInterface
    Method displayMenu()
        Display the main menu and handle user input

    Method createIndex(path)
        Create an index from documents at the given path

    Method writeIndex()
        Write the current index to a file

    Method readIndex()
        Read an index from a file

    Method enterQuery(choice, letOpen)
        Process and display the results of a query

    Method outputStatistics()
        Display statistics about the indexing process



### Used Data Structures
Explanation of what data structures are used where. For each, state
    - time and space complexity (Big-Oh),
    - why it is the appropriate data structure and what other data structure could have been used.
>AvlTree:
Complexity: Time - O(log n) for insertions and searches, Space - O(n).
- Chosen for its balanced nature, ensuring O(log n) operations. Binary search trees could have been used but might become unbalanced.
>Map:
Complexity: Time - O(log n) for lookups, insertions, and deletions, Space - O(n).
- Used for efficient key-value storage and retrieval. An alternative could be a hash map, which offers O(1) time complexity but lacks order.
>Set:
Complexity: Time - O(log n) for insertions, deletions, and lookups, Space - O(n).
- Ensures unique elements and provides ordered storage, useful for people and organization names.


### User Documentation
- What are the features of your software?

Index creation from JSON documents.
Persistent storage of indexes.
Query processing with support for organizations and people.
Statistical output of the indexing process.

- Describe how to use the software.
Create Index: Input the directory path containing JSON documents.
Write Index: Save the created index to files for persistence.
Read Index: Load an index from previously saved files.
Enter Query: Input a search query. Special operators like "org:" and "person:" can be used.
Output Statistics: View statistics like the time taken for indexing and counts of words, documents, etc.

- Some example queries with the results.

>query: german
    >result: 
what we type in terminal: oogut@genuse54.engr.smu.edu$ /users7/cse/oogut/assignment-4-search-engine-ctrl-freaks-8/build/supersearch query german
>output:
Reading index from persistence...
1
Title:  German firms doing business in UK gloomy about Brexit - survey
UUID: e17252151a2d36344b7104d14805414a55042abe
Author:  Reuters Editorial
Published: 2018-02-27T20:09:00.000+02:00

>query: january
    >result:
what we type in terminal: oogut@genuse54.engr.smu.edu$ /users7/cse/oogut/assignment-4-search-engine-ctrl-freaks-8/build/supersearch query january
>output:
Reading index from persistence...
1
Title:  Eaton Vance Closed-End Funds Release Estimated Sources Of Distributions
UUID: 4ad75456ae0bc42beeee2ff65fa58fa1cc503be2
Author:  cnbc.com
Published: 2018-02-28T18:54:00.000+02:00

2
Title:  BRIEF-Strax Ab Result For Period Jan 1 - Dec 31 2017 amounted to 0.03 Euros Per Share​
UUID: 5293252386bb424828d17b0ac60299cb52a8ecb9
Author:  Reuters Editorial
Published: 2018-02-28T04:00:00.000+02:00

### Performance
- Provide statistics (word counts, timing, etc) for indexing all documents (or as many as you can in a reasonable amount of time).

    >  Our code was able to index the documents in 0.203 seconds, Depending on the Query the time at which the program completes varies but
       ranges from 0.2 - 0.3 seconds.
       
### Bonus Work
Did you attempt any bonuses? If so, please give a brief description of what you did.

   > For the bonus work, we focused on enhancing the efficiency and accuracy of the query processing and ranking algorithm. 
   - Advanced Ranking: Implemented a sophisticated ranking system for search results, likely using a variant of the TF-IDF (Term Frequency-Inverse Document Frequency) algorithm.
   - Optimized Query Processing: 
        - Included capabilities to handle Boolean operators (AND, OR, NOT) allowing users to refine their search queries more effectively.
        - Optimized the processing of query terms, especially for complex queries involving multiple keywords, organizations, and person names.
