"""

Goal: Build a generic library that can take in multiple data sources and abstract the queries under a single API.

Data sources (and it's interfaces) are already provided, the library stitches them as appropriate for the given query/call.  Actual source of data (file vs service vs DB vs etc.) is abstracted and the library need not bother.

Example sources:
S1: product_id -> product_name, description, manufacturer_id
S2: manufacturer_id -> region_id, region_name, etc.
S3: date, product_id -> price
S4: order_id -> date, product_id, units, amount
so on...


API params : (data-cut, values, filters) => analogous to (group_by, select values, where clause)
API call 1 : fetch_data('date', 'amount', manufacturer_id=23, date=[20240101, ..., 20240201])
    SELECT date, sum(amount) FROM S1 JOIN S4 ON product_id GROUP BY date
API call 2 : fetch_data('date, region_name', 'amount', manufacturer_id=23)

select values:
 1) Agg - SUM, etc.
 2) Custom ones - being able to plug an analytical function -- (good to have)


* Better representation of the Data Source graph
* Fetch minimum data (filter pushdown)
* Use the right join algorithm ?

"""

from abc import ABC
from collections import defaultdict

class DataSource(ABC):
    
    def __init__(self, name):
        self.name = name
        self.schema = [
            # List of columns
        ]
    
    def fetch_data(self, **kwargs):
        pass

class QueryEngine():
    
    def __init__(self):
        self.sources = [
            DataSource("S1", ["product_id", "product_name", "description", "manufacturer_id"]),
            DataSource("S2", []),
            DataSource("S3", []),
            DataSource("S4", []),
        ]
        
        # Build a graph
        src_to_cols = defaultdict(list)
        
        # {"S1": [],  }
        for ds in self.sources:
            src_to_cols[ds].extend(ds.schema)
        
        cols_to_src = defaultdict(list)
        
        # { "manufact_id": [S1], "product_id": [S1, S4] }
        for ds in self.sources:
            for col in ds.schema:
                cols_to_src[col].append(ds)
        
    
    def add_source(self, source):
        self.sources.append(source)
        
    def fetch_data(self, data_cut, values, *filters):
        
        # Figure out data sources involved
        # and their associated columns
        
        # Start from cols in filters & reach all cols in values
        Q = []
        
        
        srcs = []
        
        # Fetch data for those columns from individual sources
        
        # Join across sources and create a new "source"
        # 
        
        # Perform GroupBy & Aggregation
        groups = {}
        # 
        
