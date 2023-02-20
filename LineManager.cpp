// Name: Furkan Veli Ozalp
// Seneca Student ID: 157580200
// Seneca email: fvozalp@myseneca.ca
// Date of completion: 2022-07-02
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#include <fstream>
#include <algorithm>
#include "Utilities.h"
#include "Workstation.h"
#include "LineManager.h"
namespace sdds {

    LineManager::LineManager(const std::string& file, const std::vector<Workstation*>& stations)
    {
        std::ifstream File(file);
        if (!File) {
            throw "Unable to Open file.";
        }
        else {
            Utilities ut;
            bool more;
            size_t pos = 0;

            std::string fileLine, currentWSname, nextWSname;

            Workstation* firstWS = nullptr;
            Workstation* nextWS = nullptr;
            Workstation* currentWS = nullptr;
            
            while (std::getline(File, fileLine))
            {
                currentWSname = ut.extractToken(fileLine, pos, more);
                currentWS = *std::find_if(stations.begin(), stations.end(), [&](Workstation* ws) {
                    return ws->getItemName() == currentWSname;
                   });
                m_activeLine.push_back(currentWS);

                if (more) {
                    nextWSname = ut.extractToken(fileLine, pos, more);
                    nextWS = *std::find_if(stations.begin(), stations.end(), [&](Workstation* ws) {
                        return ws->getItemName() == nextWSname;
                        });
                    currentWS->setNextStation(nextWS);
                }
            }

            for_each(stations.begin(), stations.end(), [&](Workstation* tmp) {
                firstWS = *find_if(stations.begin(), stations.end(), [&](Workstation* station) {
                    return station->getNextStation() == firstWS;
                    });
                });

            m_firstStation = firstWS;
        }
        File.close();
        m_cntCustomerOrder = g_pending.size();
    }

    void LineManager::reorderStations()
    {
        const Workstation* workstation = m_firstStation;
        size_t i{ 0 };
        do
        {
            m_activeLine[i++] = const_cast<Workstation*>(workstation);
            workstation = workstation->getNextStation();
        } while (workstation != nullptr);
    }

    bool LineManager::run(std::ostream& os) {
        static size_t count = 0;
        os << "Line Manager Iteration: " << ++count << std::endl;

        if (!g_pending.empty()) {
            *m_firstStation += std::move(g_pending.front());
            g_pending.pop_front();
        }

        std::for_each(m_activeLine.begin(), m_activeLine.end(), [&os](Workstation* ws) {
            ws->fill(os);
            });
        std::for_each(m_activeLine.begin(), m_activeLine.end(), [](Workstation* ws) {
            ws->attemptToMoveOrder();
            });

        return m_cntCustomerOrder == (g_completed.size() + g_incomplete.size());
    }

    void LineManager::display(std::ostream& os) const
    {
        if (!m_activeLine.empty()) {
            for (auto& i : m_activeLine)
                i->display(os);
        }
    }
}