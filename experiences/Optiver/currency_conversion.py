import math
import os
import random
import re
import sys


from collections import defaultdict

class ExchangeRateCalculator:
    
    @staticmethod
    def parse_rates(ccy_rates):
        for rate in ccy_rates:
            yield (rate[:3], rate[3:6], float(rate[7:]))
    
    @staticmethod
    def create_ccy_graph(parsed_rates):
        """Graph G is Represented in adjacency list form"""
        graph = defaultdict(list)
        
        for base, quote, rate in parsed_rates:
            graph[base].append((quote, rate))
            # TEST THIS!
            graph[quote].append((base, 1/rate))
        
        return graph
    
    @staticmethod
    def calculate(ccy_value, ccy_pair, ccy_rates):
        # Parse these rates into 3-tuples
        parsed_rates = list(ExchangeRateCalculator.parse_rates(ccy_rates))
        
        # This should've been created on class init
        # Make a graph out of the rates provided!
        G = ExchangeRateCalculator.create_ccy_graph(parsed_rates)
        
        # Do a BFS on G from base to quote?
        base, quote = ccy_pair[:3], ccy_pair[3:]
        
        # Could just make do with a list here!
        Q = []
        visited = set()
        
        Q.append((base, 1))
        
        # All rates of getting quote
        routes = []
        
        # Upgrade to dijkstra!
        while Q:
            ccy, r = Q.pop(0)
            # print(ccy, quote)
            
            if ccy == quote:  # end?
                routes.append(r * ccy_value)
            elif ccy not in visited:
                # Relaxation step from dijkstra!
                for nbr_ccy, nbr_rate in G[ccy]:
                    Q.append((nbr_ccy, r * nbr_rate))

                visited.add(ccy)
        
        if routes:
            return round(min(routes))
        else:
            # This tells you that the base can't be converted into quote
            # Add a test for this as well!
            return -1
    
class TestERC:
    
    def single(self):
        ERC = ExchangeRateCalculator()
        
        # Taken from the input case provided
        rates = [
            "AUDEUR@2",
            "AUDCNY@4",
            "EURJPY@5",
        ]
        
        ans = ERC.calculate(10, "AUDEUR", rates)
        assert(ans)
        
        ans = ERC.calculate(10, "AUDCNY", rates)
        print(ans)
        
        ans = ERC.calculate(10, "AUDEUR", rates)
        print(ans)
        
        # parsed_rates = list(ERC.parse_rates(rates))
        # print(parsed_rates)
        
        # G = ExchangeRateCalculator.create_ccy_graph(parsed_rates)
        # print(G)
        
    
    def alexey(self):
        ERC = ExchangeRateCalculator()
        
        # Taken from the input case provided
        rates = [
            "AUDEUR@0.6216",
            "AUDCNY@4.714",
            "CNYJPY@17.08",
            "EURJPY@129.52",
            "JPYGBP@0.006614",
            "GBPCNY@8.852",
            
        ]
        # ERC.calculate(100, "AUDEUR", rates)
        parsed_rates = list(ERC.parse_rates(rates))
        print(parsed_rates)
        
        G = ExchangeRateCalculator.create_ccy_graph(parsed_rates)
        print(G)
        
        
    def extended():
        pass
        
    def edge_cases():
        pass
        

# TestERC().single()
# exit(0)

if __name__ == '__main__':
    fptr = open(os.environ['OUTPUT_PATH'], 'w')

    ccy_value = int(input().strip())
    ccy_pair = input()
    ccy_rates_count = int(input().strip())

    # Read ccy_rates from the file!
    ccy_rates = []
    for _ in range(ccy_rates_count):
        ccy_rates_item = input()
        ccy_rates.append(ccy_rates_item)

    # Instantiate our calculator
    # What do we pass in here?
    ERC = ExchangeRateCalculator

    result = ERC.calculate(ccy_value, ccy_pair, ccy_rates)

    fptr.write(str(result) + '\n')
    fptr.close()

"""
1000000

GBPAUD

6

AUDEUR@0.6216

AUDCNY@4.714

CNYJPY@17.08

EURJPY@129.52

JPYGBP@0.006614

GBPCNY@8.852


    1877811
    
    -1
    
    
    ---
    
    
    1000000

AUDGBP

6

AUDEUR@0.6216

AUDCNY@4.714

CNYJPY@17.08

EURJPY@129.53

JPYGBP@0.006614

GBPCNY@8.852

off by 1
---

1000000

AUDGBP

6

AUDEUR@0.6166

AUDCNY@4.715

CNYJPY@17.08

EURJPY@129.53

JPYGBP@0.006614

GBPCNY@8.852

"""
