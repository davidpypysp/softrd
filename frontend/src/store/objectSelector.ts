import { createAction, createReducer } from "@reduxjs/toolkit";

export const selectObject = createAction<string>("SELECT_OBJECT");

export const objectSelectorReducer = createReducer("box3", (builder) =>
    builder.addCase(selectObject, (state, action) => action.payload)
);
