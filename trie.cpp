#include <cstdlib>
#include <string>
#include <iostream>
#include <iomanip>
#include <iterator>
#include <fstream>
#include <vector>
#include <algorithm>
#include <stack>
#include <sstream>
using namespace std;

#include "trie.h"

class Node
{
public:
	char	key_;
	size_t	id_;
	typedef vector<class Node> Nodes;
	Nodes	children_;
	size_t 	word_count_;

	void add(const string& word);
	vector<string> find(const string& target);

	static const size_t InvalidID = 0;
	static size_t LastID;

	Node() : key_(), id_(InvalidID), word_count_(0) {}; 
	bool operator == (char c) const { return key_ == c; }
};

size_t Node::LastID = 0;

vector<string> Node::find(const string& target)
{
	// find every match of this word
	// an exact match will be placed at the first element of the return vector
	// with longer matches (substr's) to follow
	//
	// perform a preorder DFS to find matches until we get to the deepest leaf
	//
	
	string::const_iterator it_target = target.begin();
	vector<const Node*> trail;
	trail.insert(trail.begin(), this);
	// find the target string, if we can
	for( string check=target; !trail.empty() && !check.empty(); )
	{
		const Node* cur = trail.front();
		// find the next child
		const char& c = check[0];
		Nodes::const_iterator next = std::find(cur->children_.begin(), cur->children_.end(), c);
		if( next == cur->children_.end() )
		{
			// no match found -- word not in trie
			return vector<string>();
		}
		// push the child on to the stack & traverse
		check.erase(check.begin());
		trail.insert(trail.begin(), &(*next));
	}

	vector<string> matches;

	// verify there is a leaf here
	Nodes::const_iterator leaf = std::find(trail.front()->children_.begin(), trail.front()->children_.end(), '\0');
	if( leaf != trail.front()->children_.end() )
	{
		stringstream ss;
		ss << "{" << setw(6) << right << leaf->id_ << "}\t";
		// assemble the current match by walking thr trail
		string match;
		for( vector<const Node*>::const_iterator follow = trail.begin(); trail.end() != follow; ++follow )
			match.push_back((*follow)->key_);
		std::reverse(match.begin(), match.end());
		ss << match; 
		matches.push_back(ss.str());
	}
	else
	{
		// there's no leaf, so there's no match.  bail
		return matches;	// it's empty
	}

	return matches;

}

void Node::add(const string& word)
{
	if( word[0] == 'h' && word[1] == 'e' && word[2] == 'l' && word[3] == 'l' )
		bool bk = true;

	Node* cur = this, *root = this;
	for( string::const_iterator it_c = word.begin(); it_c != word.end(); ++it_c )
	{
		const char& c = *it_c;
		// find the child node matching this key
		Nodes::iterator child = std::find(cur->children_.begin(), cur->children_.end(), c);
		if( child == cur->children_.end() )
		{
			// child not found -- add one
			child = cur->children_.insert(cur->children_.end(), Node());
			child->key_ = c;
		}

		// move to the pointed child
		cur = &(*child);
	}

	// insert the leaf node here
	// verify that there isn't already a leaf node at this point
	Nodes::iterator leaf = std::find(cur->children_.begin(), cur->children_.end(), '\0');
	if( leaf != cur->children_.end() )
		throw(string("Duplicate Entry!"));

	leaf = cur->children_.insert(cur->children_.end(), Node());
	leaf->key_ = '\0';
	leaf->id_ = ++LastID;
	++cur->word_count_;
	++root->word_count_;
}

string words [] =
{
"hell",
"hellandite",
"hellanodic",
"hell-begotten",
"hellbender",
"hell-bent",
"hellbent",
"hell-bind",
"hell-black",
"hellbore",
"hell-born",
"hellborn",
"hell-bound",
"hellbox",
"hellboxes",
"hell-bred",
"hellbred",
"hell-brewed",
"hellbroth",
"hell-cat",
"hellcat",
"hellcats",
"hell-dark",
"hell-deep",
"hell-devil",
"hell-diver",
"helldiver",
"helldog",
"hell-doomed",
"hell-driver",
"helleboraceous",
"helleboraster",
"hellebore",
"helleborein",
"hellebores",
"helleboric",
"helleborin",
"helleborine",
"helleborism",
"helled",
"hellene",
"hellenes",
"hell-engendered",
"hellenian",
"hellenic",
"hellenism",
"hellenist",
"hellenistic",
"hellenists",
"hellenization",
"hellenize",
"heller",
"helleri",
"helleries",
"hellers",
"hellery",
"hellespont",
"hell-fire",
"hellfire",
"hell-fired",
"hellfires",
"hell-for-leather",
"hell-gate",
"hellgrammite",
"hellgrammites",
"hellhag",
"hell-hard",
"hell-hatched",
"hell-haunted",
"hellhole",
"hellholes",
"hell-hound",
"hellhound",
"hellicat",
"hellicate",
"hellier",
"hellim",
"helling",
"hellion",
"hellions",
"hellish",
"hellishly",
"hellishness",
"hellkite",
"hellkites",
"hell-like",
"hellman",
"hellness",
"hello",
"helloed",
"helloes",
"helloing",
"hellos",
"hell-raiser",
"hell-raker",
"hell-red",
"hellroot",
"hells",
"hellship",
"helluo",
"helluva",
"hell-vine",
"hellvine",
"hellward",
"hellweed",
"helly",
};

size_t words_n = sizeof(words)/sizeof(words[0]);

void trie()
{
	Node root;

//	ifstream if_words("/usr/share/dict/words");
//	ifstream if_words("hell.dict");
	ifstream if_words("master.dict");
	cout << "Loading Words..." << endl;

	string word;
	while( getline(if_words,word) )
	{
		if( word.find("helizitic") != string::npos )
		{
			cout << word << endl;
		}
		if( word.find("hell") != string::npos )
		{
			cout << word << endl;
		}
		root.add(word);
	}

//	for( size_t i = 0; i < sizeof(words)/sizeof(words[0]); ++i )
//		root.add(words[i]);

	cout << "Loaded " << root.word_count_ << " words." << endl;

	cout << "Enter a word to search for" << endl;
	for( string s; cin >> s; cin >> s, cout << "Enter another word" << endl )
	{
		vector<string> matches = root.find(s);
		cout << matches.size() << " matches: \n\t";
		copy(matches.begin(), matches.end(), ostream_iterator<string>(cout,"\n\t")); 
		cout << endl;
	}
}

