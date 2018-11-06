#include <map>
#include <vector>



/*!
  This is a network of nodes with bidirectional links: if <b>(a, b)</b> is a link then <b>(b, a)</b> is also a link.

  Each node supports a *double* value, and the list of nodes is in fact defined by the list of their values.
 */

class Network {

public:
    Network() {}

/*! Resizes the list of nodes (\ref values) and also resets all values
	After this function is called \ref values has size *n* and contains 
	random numbers (normal distribution, mean=0, sd=1) 
*/
//change le nombre de noeuds dans le network
    void resize(const size_t&);
    
/*! Adds a bidirectional link between two nodes
  @param[in] a,b the indexes if the two nodes 
  @param[out] success the link was succesfully inserted (true if both nodes exist and the link did not exist yet)
*/
 //ajouter un neighbor à une key !! bidirectionel, changer pour le noeud ajouté aussi, comparer le nombre de liens avant-après, change uniquement multimap
    bool add_link(const size_t&, const size_t&);
    
/*! Creates random connections between nodes: each node *n* will be linked with *degree(n)* other nodes (randomly chosen) where *degree(n)* is Poisson-distributed.
  All previous links are erased first.
   @param[in] mean_deg the average of the Poisson distribution,
   @param[out] the number of links created.
*/
 //t'enlèves le lien avec tous les noeuds !! enlever aussi pour les autres noeuds, retourne le nombre de link total dans la multimap
    size_t random_connect(const double&);
    
/*! Resets node values with a vector of *n* new values.
   If the current size is *s* and *n<s* then only the first *n* values are changed.
   If *n>s* then only *s* values are used. 
   The internal \ref values vector keeps the same size.

   @param[in] vector of new node values,
   @param[out] number of nodes succesfully reset.
*/
 //affecte values avec un un nouveau tableau de valeur, renvoyer la taille du tableau en paramètre
    size_t set_values(const std::vector<double>&);
    
/*! Number of nodes */
//nombre de noeuds dans le network, taille de values
    size_t size() const;
    
/*! Degree (number of links) of node no *n* */
//nombre de valeurs associées à une key, prend en paramètre la position du noeud dans values => values[n]=key dans multimap
    size_t degree(const size_t &_n) const;
    
/*! Value of node no *n* */
//nom du noeud, key associée, renvoie values[n]
    double value(const size_t &_n) const;
    
/*! All node values in descending order 
	\ref values is left unchanged by this operation
*/
//organiser les noeuds dans l'ordre décroissante
    std::vector<double> sorted_values() const;
    
/*! All neighbors (linked) nodes of node no *n* */
//renvoie un tableau avec les positions dans values de chaque voisin
    std::vector<size_t> neighbors(const size_t&) const;

private:
    std::vector<double> values;
    std::multimap<size_t, size_t> links;

};
