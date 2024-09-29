/*
## Scope

Design a High Performing Database

Focussed on reads

Data looks Tabular - Securities (with identifier) -> Risk metrics, Referential
Data

Timeseries component - per date

Portfolio is a group of securities - arbitrary groupings

Given, date, portfolio - give me *some* columns of *all* securities


## Approach

Key -> Arrow/Proto

DATE:PORTID:SECID

Prefix scan

## Storage
*/

// struct
// protobuf

Page - PageHeader PageData

           map<DPSKey, Page>
               storage;

unordered_map<Key, RowPtr> index;
map<PDKey, RowPtr> index2;

map<DKey, PagePtr> index2;

// LSMTrees
