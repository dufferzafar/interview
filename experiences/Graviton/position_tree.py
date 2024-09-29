"""
We have n files containing trades (1 file per strategy)
time,strategy_id, trade_id, side, symbol, px, qty

And a file containing prices data for every symbol every sec
time, symbol, mid, last_trade_price

Read these n+1 files and calculate the pnl of our n strategies

Store the pnl, symbol x time calculated metrics/pnls, in such a way that
We will send the whole calculated data from the beginning till now
We will send periodic updates (10s), few symbols


Ingestion Layer:
"""
For trade_file in files:
Fd = open(trade_file)
epoll.register(fd)

Consumer Thread:

While True:
Events = self.epoll.poll()

For fd, event in events:
pass

Calculation Layer:

Class Trade:
	Symbol
	Side

Class PriceUpdate:
	Symbol
	Price


Class PnlMetrics():
	Qty
	Mkt_value
	Total_pnl
	
	Def handle_trade(trade):
	Pass

Def handle_px_update(px):
	pass
	

class Node():
parents = []
Latest = false
Level = “Symbol” | “Venue” | “Strategy”
metrics = PnlMetrics()	

Def handle_trade(trade):
	self.latest = false
	self.metrics.handle_trade(trade)
	For p in self.parents():
		p.handle_trade(trade)

Def handle_px_update(px):
self.latest = false
	self.metrics.handle_px_update(px)
For p in self.parents():
		p.handle_px_update(trade)


Root = Node()
