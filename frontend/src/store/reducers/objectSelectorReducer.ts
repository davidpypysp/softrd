const objectSelectorReducer = (state: string = "box3", action) => {
    switch (action.type) {
        case "SELECT_OBJECT":
            return action.id;
        default:
            return state;
    }
};

export default objectSelectorReducer;
