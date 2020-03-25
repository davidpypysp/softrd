import { combineReducers } from 'redux'
import objectListReducer from "src/store/reducers/objectListReducer";
import objectSelectorReducer from "src/store/reducers/objectSelectorReducer";

export default combineReducers({
    objectList: objectListReducer,
    objectSelector: objectSelectorReducer
});
