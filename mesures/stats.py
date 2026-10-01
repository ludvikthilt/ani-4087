#!/usr/bin/env python3
"""Usage : python stats.py 1.2 1.3 1.1 ...  -> n, moyenne, mediane, ecart-type (echantillon), min, max"""
import sys, statistics as st
vals = [float(v.replace(",", ".")) for v in sys.argv[1:]]
if not vals:
    sys.exit("Donnez au moins une valeur.")
print(f"n        = {len(vals)}")
print(f"moyenne  = {st.mean(vals):.4f}")
print(f"mediane  = {st.median(vals):.4f}")
print(f"ecart-type (n-1) = {st.stdev(vals):.4f}" if len(vals) > 1 else "ecart-type = n/a (n=1)")
print(f"min / max = {min(vals):.4f} / {max(vals):.4f}")
