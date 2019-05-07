
#include "set.h"

void print( std::ostream& out, const treenode* n, size_t indent )
{

   for( size_t i = 0; i != indent; ++ i )
      out << "|  ";
   if(n)
   {
      out << ( n -> val ) << "\n";
      print( out, n -> left, indent + 1 );
      print( out, n -> right, indent + 1 );
   }
   else
      out << "#\n";
}


void checksorted(
          treenode* n,
          const std::string* lowerbound,
          const std::string* upperbound )
{
   while(n)
   {
      if( lowerbound && !before( *lowerbound, n -> val ))
      {
         std::cout << "value " << ( n -> val );
         std::cout << " is not above lower bound " << *lowerbound << "\n";
         std::abort( );
      }

      if( upperbound && !before( n -> val, *upperbound ))
      {
         std::cout << "value " << ( n -> val );
         std::cout << "is not below upperbound " << *upperbound << "\n";
         std::abort( );
      }

      checksorted( n -> left, lowerbound, &( n -> val ));
      lowerbound = & ( n -> val );
      n = n -> right;
   }
}


// Used by copy constructor and assignment:

void writecopy( treenode** to, treenode* from )
{
   while( from )
   {
      *to = new treenode{ from -> val };

      writecopy( & (*to) -> left, from -> left );
      to = & (*to) -> right;
      from = from -> right;
   }
}

// Used by destructor:

void deallocate( treenode* n )
{
   while(n)
   {
      deallocate( n -> left );
      treenode* bye = n;
      n = n -> right;
      delete bye;
   }
}



size_t log_base2( size_t s )
{
    int cnt = 0;

    if(s == 0)
    {
        return 0;
    }
    else {
        while(s / 2 > 0)
        {
            s = s / 2;
            cnt++;
        }
        return cnt;
    }
}
// From previous task:

bool equal( const std::string& s1, const std::string& s2 )
{
    if( s1.length() == s2.length() )
    {
        for( unsigned int i = 0; i < s1.length(); ++i )
        {
            if( tolower(s1[i])!= tolower(s2[i]) )
                return false;
        }
        return true;
   	} else {
        return false;
   	}
}
// Must be written for task 5(part 2) :

bool before( const std::string& s1, const std::string& s2 )
{
    if (equal(s1, s2))
    {
        return false;
    }
    else
    {
        char let1, let2;
        for ( size_t i = 0; i < s1.length(); i++)
    {
        let1 = s1[i];
        let2= s2[i];
        if(tolower(let1) < tolower(let2))
            return true;
        else if (tolower(let1) > tolower(let2))
            return false;
    }
    return true;
    }
}

const treenode* find( const treenode* n, const std::string& el )
{
    if (n == nullptr)
        return n;
    else if (before(n -> val, el))
        return find (n->right, el);
    else if (equal (n -> val, el))
        return n;
    else
        return find (n->left, el);

    return n;
}
   // Write this one first.

treenode** find( treenode** n, const std::string& el )
{
    if ((*n) == nullptr)
        return n;
    else if (before((*n) -> val, el))
        return find (&(*n)->right, el);
    else if (equal ((*n) -> val, el))
        return n;
    else
        return find (&(*n)->left, el);

    return n;
}
   // Modify the other find into this one, also have a look at
   // stackscan4.pdf


// Insert n at the right most position in into:

void rightinsert( treenode** into, treenode* n )
{
    if ((*into) -> right == NULL)
        (*into)-> right = n;
    else if ((*into) -> right != NULL)
        rightinsert(&((*into)->right), n);
}

size_t size( const treenode* n )
{
    if (n == NULL)
        return 0;
    else
        return(size(n->left) + 1 + size(n->right));
}

size_t height( const treenode* n )
{
    if (n == NULL)
    {
        return 0;
    } else {
        size_t heightl = height(n->left);
        size_t heightr = height(n->right);

        if (heightl > heightr)
            return(heightl + 1);
        else
            return(heightr + 1);
    }
}

bool set::insert( const std::string& el )
{
    treenode **temp = find(& tr, el);
    if (*temp == NULL)
    {
        *temp = new treenode(el);
        return true;
    }
    else if (*temp != NULL)
    {
        return false;
    }

}

bool set::contains( const std::string& el ) const
{
   return find( tr, el ) != nullptr;
}


bool set::remove( const std::string& el )
{
    treenode** temp = find(&tr, el);

    if (*temp != NULL)
    {
        if ((*temp)->right == NULL && (*temp)->left == NULL)
        {
            delete *temp;
            *temp = NULL;
        }
        else if ((*temp) -> right == NULL)
        {
            treenode* temp_right_copy = *temp;
            *temp = (*temp) -> left;
            delete temp_right_copy;
        }
        else if ((*temp) -> left == NULL)
        {
            treenode* temp_left_copy = *temp;
            *temp = (*temp) -> right;
            delete temp_left_copy;
        }
        else
        {
            treenode* temp_copy = *temp;
            rightinsert(&((*temp)->left), (*temp)->right);
            *temp = (*temp) -> left;
            delete temp_copy;
        }
        return true;
    } else {
        return false;
    }
}

void set::checksorted( ) const
{
   ::checksorted( tr, nullptr, nullptr );
      // :: are needed because the other checksorted is not in the class.
}


std::ostream& set::print( size_t indent, std::ostream& out ) const
{
   ::print( out, tr, indent );
   return out;
}


