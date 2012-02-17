/// @file AesopSimpleWorldState.h
/// @brief Definition of SimpleWorldState class.

#ifndef _AE_SIMPLE_WORLDSTATE_H_
#define _AE_SIMPLE_WORLDSTATE_H_

#include <vector>
#include "AesopWorldState.h"

namespace Aesop {
   /// @brief Simplest WorldState implementation.
   /// @ingroup Aesop
   class SimpleWorldState : public WorldState {
   public:
      /// @name WorldState
      /// @{

      virtual bool isSet(Predicates::predID pred, const paramlist &params = paramlist()) const;
      virtual void set(Predicates::predID pred, const paramlist &params = paramlist());
      virtual void unset(Predicates::predID pred, const paramlist &params = paramlist());
      virtual WorldState *clone() const;
      virtual std::string repr() const;

      unsigned int compare(const WorldState &other) const;

      virtual bool operator==(const WorldState &other) const
      {
         const SimpleWorldState *ws = dynamic_cast<const SimpleWorldState*>(&other);
         return ws != 0 && mHash != ws->mHash ? false : compare(*ws) == 0;
      }
      virtual bool operator!=(const WorldState &other) const
      {
         const SimpleWorldState *ws = dynamic_cast<const SimpleWorldState*>(&other);
         return ws == 0 || mHash != ws->mHash ? true : compare(*ws) != 0;
      }

      /// @}

      SimpleWorldState(const Predicates &p);
      ~SimpleWorldState();

   protected:
   private:
      /// @brief Set a predicate without updating our hash.
      /// @see WorldState::set
      void _set(Predicates::predID pred, const paramlist &params);
      /// @brief Unset a predicate without updating our hash.
      /// @see WorldState::unset
      void _unset(Predicates::predID pred, const paramlist &params);

      /// @brief Hashed representation of this state, used for quick comparison.
      int mHash;
      /// @brief Update our hash value.
      void updateHash();

      /// @brief Store a fact about the world.
      struct fact {
         /// @brief Is this predicate set?
         bool set;
         fact() : set(false) {}
      };
      /// @brief Our world representation is simply a list of facts.
      typedef std::vector<fact> worldrep;
      /// @brief Stores representation of world state.
      worldrep mState;
   };
};

#endif
