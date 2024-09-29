"""
C++ Security Data Service

~500 fields, 500,000 instruments
100 field classes

DAG of dependencies

How will I model the DAG?
"""

from collections import defaultdict

Graph = {}

# Leaf
class Field():
    name = ""
    deps = []
    dirty = False
    # updated_at = now()

    # mktval = {pos, px}
    Graph[Field] = deps
    
    # pos -> mktval
    # px -> mktval
    ParentGraph = defaultdict(list)
    for d in deps:
        ParentGraph[d].append(Field)

    def getValue(Security):
        return Security.mktval

    def updateValue(Security):
        # eval()
        # pass
        Security.mktval = Security.pos * Security.px
        
    def __init__(self, name, value):
        pass
        

# Toposorted field list
# 
OrderedFields = [name, pos, px, bod_pos, bod_px, id_mktval, bod_mktval, pnl]

# DAG
class FieldDAG:
    name = Field()
    px = Field()
    pos = Field()
    bod_pos = Field()
    id_mktval = Field("mktval", [px, pos], "px*pos")
    bod_mktval = Field("", [bod_px, bod_pos])
    pnl = Field("", [bod_mkt, id_mktval])
        
    def toposort():
        # Figure out which fields need to be recomputed
        # Topology sort of the graph
        # needs to be done once, at startup!
        pass

class Security():

    # {"mktval": 9000, "pos": 100, "px": 10.1}
    def __init__(**fields):
        # self.fields = fields
        self.pos = Field("pos", val)
        self.bod_pos = Field("bod_pos", val)
    
    def updateField(field, new_val):
        # update the fields dict?
        pass
    
    def recompute():
        # Recompute them!
        for field in OrderedFields:
            if field.dirty():
                # Update all its parents
                for parent in ParentGraph[field]:
                    parent.updateValue(self)

class Stock(Security):
    
    def __init__(self, **fields):
        super().__init__(fields)
        # self.specific_fields = 

        

s = Security()
s.recompute()

# Security.recomputeMany([
#     s1, s2, s3
# ])

# Security.recomputeAll()

