import pandas as pd

data = [
    # Order ID, Instrument, Side, Action, Qty, Price
    [1, 'AAPL', 'buy', 'order', 100, 55.10],
    [2, 'MSFT', 'buy', 'order', 200, 40.50],
    [2, 'MSFT', 'buy', 'trade', 100, 40.50],
    [1, 'AAPL', 'buy', 'trade', 10, 55.10],
    [1, 'AAPL', 'buy', 'trade', 40, 55.10],
    [1, 'AAPL', 'buy', 'trade', 50, 55.10],
    [2, 'MSFT', 'buy', 'trade', 100, 40.50],
    [3, 'AAPL', 'sell', 'order', 100, 55.10],
    [4, 'MSFT', 'sell', 'order', 200, 40.50],
    [4, 'MSFT', 'sell', 'trade', 100, 40.50],
    [4, 'MSFT', 'sell', 'trade', 100, 40.50],
    [3, 'AAPL', 'sell', 'trade', 10, 55.10],
    [3, 'AAPL', 'sell', 'trade', 40, 55.10],
    [3, 'AAPL', 'sell', 'trade', 50, 55.10],
]

df = pd.DataFrame(data, columns=['orderid', 'symbol', 'side', 'action', 'qty', 'price'])

# These columns represent enums
df['side'] = pd.Categorical(df['side'])
df['action'] = pd.Categorical(df['action'])

# Ratio of the order that was filled = trade_qty / order_qty
# Naive way requires a groupby and picking the first row per orderid
df['fill_ratio'] = df['qty'] / df.groupby('orderid')['qty'].transform('first')

# Better way: use cummax to find the first order for each orderid
# And then use searchsorted to find the index of the first order for each row!
# This works because the orderid is always increasing!

# For each row, find the index of the first order that was placed for the same orderid
df['order_idx'] = df['orderid'].cummax().searchsorted(df['orderid'])

# Use the idx to find attributes of the initial order, like qty!
df['order_qty'] = df.loc[df['order_idx']]['qty'].reset_index(drop=True)
df['fill_ratio'] = df['qty'] / df['order_qty']

# We can reuse the order_idx to find other attributes from the first order, like price
df['order_price'] = df.loc[df['order_idx']]['price'].reset_index(drop=True)

# Counting the number of events that have happened for each order
# Can be done via groupby as well
df["event_count"] = df.groupby("orderid").cumcount() + 1

# Or using expanding, which is more flexible, but quadratic in time
df["event_count"] = df["orderid"].expanding().apply(lambda x: (x == x.iloc[-1]).sum())
