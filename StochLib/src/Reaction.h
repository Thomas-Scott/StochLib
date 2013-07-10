#ifndef __REACTION__
#define __REACTION__


struct Reaction{
	int reactionID;
	int numReactants;
	int * reactants;
	int * rates;
};

#endif // __REACTION__