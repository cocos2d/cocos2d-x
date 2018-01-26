/**
 * An OriginalLocation represents a location in an original source.
 *
 * @param SourceActor actor
 *        A SourceActor representing an original source.
 * @param Number line
 *        A line within the given source.
 * @param Number column
 *        A column within the given line.
 * @param String name
 *        The name of the symbol corresponding to this OriginalLocation.
 */

function OriginalLocation(actor, line, column, name) {
  this._connection = actor ? actor.conn : null;
  this._actorID = actor ? actor.actorID : undefined;
  this._line = line;
  this._column = column;
  this._name = name;
}

OriginalLocation.fromGeneratedLocation = function (generatedLocation) {
  return new OriginalLocation(
    generatedLocation.generatedSourceActor,
    generatedLocation.generatedLine,
    generatedLocation.generatedColumn
  );
};

OriginalLocation.prototype = {
  get originalSourceActor() {
    return this._connection ? this._connection.getActor(this._actorID) : null;
  },

  get originalUrl() {
    let actor = this.originalSourceActor;
    let source = actor.source;
    return source ? source.url : actor._originalUrl;
  },

  get originalLine() {
    return this._line;
  },

  get originalColumn() {
    return this._column;
  },

  get originalName() {
    return this._name;
  },

  get generatedSourceActor() {
    throw new Error("Shouldn't  access generatedSourceActor from an OriginalLocation");
  },

  get generatedLine() {
    throw new Error("Shouldn't access generatedLine from an OriginalLocation");
  },

  get generatedColumn() {
    throw new Error("Shouldn't access generatedColumn from an Originallocation");
  },

  equals: function (other) {
    return this.originalSourceActor.url == other.originalSourceActor.url &&
           this.originalLine === other.originalLine &&
           (this.originalColumn === undefined ||
            other.originalColumn === undefined ||
            this.originalColumn === other.originalColumn);
  },

  toJSON: function () {
    return {
      source: this.originalSourceActor.form(),
      line: this.originalLine,
      column: this.originalColumn
    };
  }
};

/**
 * A GeneratedLocation represents a location in a generated source.
 *
 * @param SourceActor actor
 *        A SourceActor representing a generated source.
 * @param Number line
 *        A line within the given source.
 * @param Number column
 *        A column within the given line.
 */
function GeneratedLocation(actor, line, column, lastColumn) {
  this._connection = actor ? actor.conn : null;
  this._actorID = actor ? actor.actorID : undefined;
  this._line = line;
  this._column = column;
  this._lastColumn = (lastColumn !== undefined) ? lastColumn : column + 1;
}

GeneratedLocation.fromOriginalLocation = function (originalLocation) {
  return new GeneratedLocation(
    originalLocation.originalSourceActor,
    originalLocation.originalLine,
    originalLocation.originalColumn
  );
};

GeneratedLocation.prototype = {
  get originalSourceActor() {
    throw new Error();
  },

  get originalUrl() {
    throw new Error("Shouldn't access originalUrl from a GeneratedLocation");
  },

  get originalLine() {
    throw new Error("Shouldn't access originalLine from a GeneratedLocation");
  },

  get originalColumn() {
    throw new Error("Shouldn't access originalColumn from a GeneratedLocation");
  },

  get originalName() {
    throw new Error("Shouldn't access originalName from a GeneratedLocation");
  },

  get generatedSourceActor() {
    return this._connection ? this._connection.getActor(this._actorID) : null;
  },

  get generatedLine() {
    return this._line;
  },

  get generatedColumn() {
    return this._column;
  },

  get generatedLastColumn() {
    return this._lastColumn;
  },

  equals: function (other) {
    return this.generatedSourceActor.url == other.generatedSourceActor.url &&
           this.generatedLine === other.generatedLine &&
           (this.generatedColumn === undefined ||
            other.generatedColumn === undefined ||
            this.generatedColumn === other.generatedColumn);
  },

  toJSON: function () {
    return {
      source: this.generatedSourceActor.form(),
      line: this.generatedLine,
      column: this.generatedColumn,
      lastColumn: this.generatedLastColumn
    };
  }
};

getOffsetColumn = function getOffsetColumn(aOffset, aScript) {
  let bestOffsetMapping = null;
  for (let offsetMapping of aScript.getAllColumnOffsets()) {
    if (!bestOffsetMapping ||
        (offsetMapping.offset <= aOffset &&
         offsetMapping.offset > bestOffsetMapping.offset)) {
      bestOffsetMapping = offsetMapping;
    }
  }

  if (!bestOffsetMapping) {
    // XXX: Try not to completely break the experience of using the debugger for
    // the user by assuming column 0. Simultaneously, report the error so that
    // there is a paper trail if the assumption is bad and the debugging
    // experience becomes wonky.
    reportError(new Error("Could not find a column for offset " + aOffset
                          + " in the script " + aScript));
    return 0;
  }

  return bestOffsetMapping.columnNumber;
}

/**
 * Construct an ActorPool.
 *
 * ActorPools are actorID -> actor mapping and storage.  These are
 * used to accumulate and quickly dispose of groups of actors that
 * share a lifetime.
 */
function ActorPool(aConnection)
{
  this.conn = aConnection;
  this._cleanups = {};
  this._actors = {};
}

ActorPool.prototype = {
  /**
   * Add an actor to the actor pool.  If the actor doesn't have an ID,
   * allocate one from the connection.
   *
   * @param aActor object
   *        The actor implementation.  If the object has a
   *        'disconnect' property, it will be called when the actor
   *        pool is cleaned up.
   */
  addActor: function AP_addActor(aActor) {
    aActor.conn = this.conn;
    if (!aActor.actorID) {
      let prefix = aActor.actorPrefix;
      if (!prefix && typeof aActor == "function") {
        // typeName is a convention used with protocol.js-based actors
        prefix = aActor.prototype.actorPrefix || aActor.prototype.typeName;
      }
      aActor.actorID = this.conn.allocID(prefix || undefined);
    }

    if (aActor.registeredPool) {
      aActor.registeredPool.removeActor(aActor);
    }
    aActor.registeredPool = this;

    this._actors[aActor.actorID] = aActor;
    if (aActor.disconnect) {
      this._cleanups[aActor.actorID] = aActor;
    }
  },

  get: function AP_get(aActorID) {
    return this._actors[aActorID] || undefined;
  },

  has: function AP_has(aActorID) {
    return aActorID in this._actors;
  },

  /**
   * Returns true if the pool is empty.
   */
  isEmpty: function AP_isEmpty() {
    return Object.keys(this._actors).length == 0;
  },

  /**
   * Remove an actor from the actor pool.
   */
  removeActor: function AP_remove(aActor) {
    delete this._actors[aActor.actorID];
    delete this._cleanups[aActor.actorID];
  },

  /**
   * Match the api expected by the protocol library.
   */
  unmanage: function(aActor) {
    return this.removeActor(aActor);
  },

  /**
   * Run all actor cleanups.
   */
  cleanup: function AP_cleanup() {
    for (let id in this._cleanups) {
      this._cleanups[id].disconnect();
    }
    this._cleanups = {};
  },

  forEach: function(callback) {
    for (let name in this._actors) {
      callback(this._actors[name]);
    }
  },
}