// Copyright (c) 2009-2012 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file license.txt or http://www.opensource.org/licenses/mit-license.php.

#include <boost/assign/list_of.hpp> // for 'map_list_of()'
#include <boost/foreach.hpp>

#include "checkpoints.h"

#include "main.h"
#include "uint256.h"

namespace Checkpoints
{
    typedef std::map<int, uint256> MapCheckpoints;

    //
    // What makes a good checkpoint block?
    // + Is surrounded by blocks with reasonable timestamps
    //   (no blocks before with a timestamp after, none after with
    //    timestamp before)
    // + Contains no strange transactions
    //
    static MapCheckpoints mapCheckpoints =
        boost::assign::map_list_of
        ( 36180, uint256("0x0000000000635e5e1a8027383f028f4c666f9e20f4f90968ba8bf7ba8431c71f"))
        (127360, uint256("0x000000000330be69aa359cb69896554c0dfcd9d76b5415d526708ed737bfe0b6"))
		(131130, uint256("0x0000000000853272e70ba9aafe9f685c186a7ba3aa57d2ddba7c44c6a25efe09"))
		(136800, uint256("0x0000000000c8c592fce349ed8cf7eba3113f3c243c9e1cbe27fb6166cc4ffa00"))
		(142900, uint256("0x00000000005eb49db6f29a6aae382b7a8e9a109aba42e536e6d74b95aba4dffd"))
		(155000, uint256("0x0000000000041a6bc4cd419ed90a6bb1dbf8df8a587d162504dba9ae84a4418c"))
		(161000, uint256("0x601581f84984f86f5c4d080b2e32bd1c4da4061730fd9bc6b4ce08c65b30c4bd"))
        ;

    bool CheckBlock(int nHeight, const uint256& hash)
    {
        if (fTestNet) return true; // Testnet has no checkpoints

        MapCheckpoints::const_iterator i = mapCheckpoints.find(nHeight);
        if (i == mapCheckpoints.end()) return true;
        return hash == i->second;
    }

    int GetTotalBlocksEstimate()
    {
        if (fTestNet) return 0;

        return mapCheckpoints.rbegin()->first;
    }

    CBlockIndex* GetLastCheckpoint(const std::map<uint256, CBlockIndex*>& mapBlockIndex)
    {
        if (fTestNet) return NULL;

        BOOST_REVERSE_FOREACH(const MapCheckpoints::value_type& i, mapCheckpoints)
        {
            const uint256& hash = i.second;
            std::map<uint256, CBlockIndex*>::const_iterator t = mapBlockIndex.find(hash);
            if (t != mapBlockIndex.end())
                return t->second;
        }
        return NULL;
    }
}
