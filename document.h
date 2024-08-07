#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <string>
using namespace std;

class document
{
    public: 
    string title;            // title of the document
    string identifier;       // unique identifier for the document
    string publicationDate;  // date when the document was published
    string authorName;       // name of the document's author
    string content;          // text content of the document
    int relevanceScore = 0;      // relevance score indicating the importance or ranking of the document


    document() = default;
    document(string t, string id, string pubDate, string author, string text) : title(t), identifier(id), publicationDate(pubDate), authorName(author), content(text) {};

//check if equal
    bool operator==(const document &other) const
    {
        return title == other.title && identifier == other.identifier && publicationDate == other.publicationDate &&
               authorName == other.authorName && relevanceScore == other.relevanceScore && content == other.content;
    }

//check if less
    bool operator<(const document &other) const 
    {
        return (other.relevanceScore < relevanceScore);
    }

//check if greater
    bool operator>(const document &other) const
    {
        return (other.relevanceScore > relevanceScore);
    }
};

#endif
